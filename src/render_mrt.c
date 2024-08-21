/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:43 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/21 20:48:02 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	get_colour(uint8_t *pixels, double *colour)
{
	int	i;

	if (!pixels)
		return ;
	i = -1;
	while (++i < 3)
	{
		if (colour[i] > 1)
			*(pixels + i) = 255;
		else if (colour[i] < 0)
			*(pixels + i) = 0;
		else
			*(pixels + i) = (uint8_t) (colour[i] * 255);
	}
	*(pixels + 3) = 255;
	return ;
}

static void	calculate_op(t_comps *comps)
{
	comps -> over_point = point(
		comps -> point_w[0] + EPSILON * comps -> normal_vec[0],
		comps -> point_w[1] + EPSILON * comps -> normal_vec[1],
		comps -> point_w[2] + EPSILON * comps -> normal_vec[2]);
}

static t_comps	*prepare_comps(double t, double **ray, t_object *obj)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps -> point_w = position(ray, t);
	comps -> obj = obj;
	comps -> normal_vec = normal_at(obj, comps -> point_w);
	comps -> eye_vec = copy_vec(ray[1], 4);
	vec_skal_prod(comps -> eye_vec, -1, 3);
	if (dot_product(comps -> normal_vec, comps -> eye_vec) < 0)
	{
		comps -> inside = true;
		vec_skal_prod(comps -> normal_vec, -1, 3);
	}
	else
		comps -> inside = false;
	calculate_op(comps);
	return (comps);
}

static double	*color_at(t_world *w, double **ray)
{
	t_intersect	*xs;
	t_intersect	*hit;
	t_comps		*comps;
	double		*colour;

	xs = intersect_world(w, ray);
	hit = find_hit(xs);
	if (hit)
	{
		comps = prepare_comps(hit -> t, ray, hit -> obj);
		colour = lighting(w, comps);
		free_comps(comps);
	}
	else
		colour = point(0, 0, 0);
	free_ray(ray);
	free_intersect(xs);
	return (colour);

}

void	render(t_world *w, t_camera *c, mlx_image_t *img)
{
	int	i;
	int	j;
	int	pixel_idx;
	double	*colour;

	i = -1;
	pixel_idx = 0;
	while (++i < HSIZE)
	{
		j = -1;
		while (++j < VSIZE)
		{
			colour = color_at(w, ray_for_pixel(c, i, j));
			pixel_idx = (j * HSIZE * 4) + (i * 4);
			get_colour((img -> pixels) + pixel_idx, colour);
		}
	}
}

/*
void	print_xs(t_intersect *xs)
{
	while (xs)
	{
		printf("%f ", xs -> t);
		xs = xs -> next;
	}
	printf("\n");
}
*/
