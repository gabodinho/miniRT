/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:41 by gabodinho         #+#    #+#             */
/*   Updated: 2024/08/21 20:37:13 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**ray(double *origin, double *direction)
{
	double	**ray;

	ray = malloc(sizeof(double *) * 2);
	// throw errror
	if (!ray)
		return (NULL);
	ray[0] = origin;
	ray[1] = direction;
	return (ray);
}

double	*position(double **ray, double t)
{
	return (point(
	ray[0][0] + t * ray[1][0],
	ray[0][1] + t * ray[1][1],
	ray[0][2] + t * ray[1][2]));
}

double	**transform(double **ray, double *m)
{
	double	**ray_obj;

	ray_obj = malloc(sizeof(double *) * 2);
	ray_obj[0] = mat_vec_prod(m, ray[0]);
	ray_obj[1] = mat_vec_prod(m, ray[1]);
	return (ray_obj);
}

int	is_shadowed(t_world *w, double *p)
{
	double	*dir;
	double	dist;
	double	**r;
	t_intersect	*xs;
	t_intersect	*hit;

	dir = substract_points(w -> light_point, p);
	dist = sqrt(pow(dir[0], 2) + pow(dir[0], 2) + pow(dir[0], 2));
	normalize(dir);
	r = ray(copy_vec(p, 4), dir);
	xs = intersect_world(w, r);
	hit = find_hit(xs);
	if (hit && hit -> t < dist)
		dist = 1;
	else
		dist = 0;
	free_ray(r);
	free_intersect(xs);
	return ((int) dist);
}


