/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:35:43 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/18 02:36:28 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	get_colour(uint8_t *pixels, double *colour)
{
	int rgba = *((int *) colour);	// only for testing puposes

	if (!pixels)
		return ;
	*pixels = (rgba >> 24) & 0xFF;
	*(pixels + 1) = (rgba >> 16) & 0xFF;
	*(pixels + 2) = (rgba >> 8) & 0xFF;
	*(pixels + 3) = (rgba) & 0xFF;
	return ;
}

t_comps	*prepare_comps(double t, double **ray, t_object *obj)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	comps -> point_w = position(ray, t);
	comps -> obj = obj;
	// comps -> normal_vec = normal_at(obj, comps -> point_w, ray);		original
		comps -> normal_vec = normal_at(obj, comps -> point_w);	//only for testing
	comps -> eye_vec = ray[1];
	vec_skal_prod(comps -> eye_vec, -1, 3);
	if (dot_product(comps -> normal_vec, comps -> eye_vec) < 0)
	{
		comps -> inside = true;
		vec_skal_prod(comps -> normal_vec, -1, 3);
	}
	else
		comps -> inside = false;
	return (comps);
}


double	*color_at(t_world *w, double **ray)
{
	t_intersect	*xs;
	t_intersect	*hit;
	t_comps		*comps;
	double		*colour;

	xs = intersect_world(w, ray);
	hit = find_hit(xs);
	if (hit)
	{
		comps = prepare_comps(xs -> t, ray, hit -> obj);
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
