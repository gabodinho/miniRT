/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:41 by gabodinho         #+#    #+#             */
/*   Updated: 2024/08/14 21:54:07 by gabodinho        ###   ########.fr       */
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

void	append_intersect(t_intersect **lst, double *xs, t_object *obj)
{
	t_intersect	*new1;
	t_intersect	*new2;
	t_intersect	*ptr;

	new1 = malloc(sizeof(t_intersect));
	new1 -> obj = obj;
	new1 -> t = xs[0];
	new1 -> next = NULL;
	if (obj -> shape != PLANE)
	{
		new2 = malloc(sizeof(t_intersect));
		new2 -> obj = obj;
		new2 -> t = xs[1];
		new1 -> next = new2;
		new2 -> next = NULL;
	}
	if (!*lst)
	{
		*lst = new1;
		return ;
	}
	ptr = *lst;
	while (ptr -> next)
		ptr = ptr -> next;
	ptr -> next = new1;
}

void	intersect_sphere(double **ray, t_object *obj, t_intersect **lst)
{
	double	*xs;
	double	*sp_to_ray;
	double	a;
	double	b;
	double	d;

	sp_to_ray = vector(ray[0][0], ray[0][1], ray[0][2]);
	a = dot_product(ray[1], ray[1]);
	b = 2 * dot_product(ray[1], sp_to_ray);
	d = b * b - 4 * a * (dot_product(sp_to_ray, sp_to_ray) - 1);
	if (d < 0)
		return ;
	xs = malloc(sizeof(double) * 2);
	// throw error
	if (!xs)
		return ;
	xs[0] = (-b - sqrt(d)) / (2 * a);
	xs[1] = (-b + sqrt(d)) / (2 * a);
	printf("inside intersect_sphere: %f %f\n", xs[0], xs[1]);
	append_intersect(lst, xs, obj);
	free(sp_to_ray);
	free(xs);
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
		// else if (ptr -> shape == CYLNDR)
		// 	intersect_cylinder(ray, ptr, &i);
		// else
		// 	intersect_plane(ray, ptr, &i);
	}
	return (i);
}
