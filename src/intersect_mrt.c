/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_mrt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:15:22 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 18:22:40 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	intersect_sphere(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[2];
	double	*sp_to_ray;
	double	temp[3];
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	sp_to_ray = vector(ray_o[0][0], ray_o[0][1], ray_o[0][2]);
	temp[0] = dot_product(ray_o[1], ray_o[1]);
	temp[1] = 2 * dot_product(ray_o[1], sp_to_ray);
	temp[2] = temp[1] * temp[1] - 4 * temp[0]
		* (dot_product(sp_to_ray, sp_to_ray) - 1);
	if (temp[2] < 0)
		return ;
	xs[0] = (-temp[1] - sqrt(temp[2])) / (2 * temp[0]);
	xs[1] = (-temp[1] + sqrt(temp[2])) / (2 * temp[0]);
	append_intersect(lst, xs, obj);
	free(sp_to_ray);
	free_ray(ray_o);
}

// standard plane lies in x-z-plane with y = 0
static void	intersect_plane(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[2];
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	if (abs_f(ray_o[1][1]) < EPSILON)
	{
		free_ray(ray_o);
		return ;
	}
	xs[0] = -ray_o[0][1] / ray_o[1][1];
	xs[1] = xs[0];
	append_intersect(lst, xs, obj);
	free_ray(ray_o);
}

t_intersect	*intersect_world(t_world *w, double **ray)
{
	t_intersect	*i;
	int			k;
	t_object	*ptr;

	i = NULL;
	k = -1;
	while (++k < w -> n_obj)
	{
		ptr = w -> objects[k];
		if (ptr -> shape == SPHERE)
			intersect_sphere(ray, ptr, &i);
		else if (ptr -> shape == CYLNDR)
			intersect_cylinder(ray, ptr, &i);
		else
			intersect_plane(ray, ptr, &i);
	}
	return (i);
}
