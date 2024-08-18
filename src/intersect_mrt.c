/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_mrt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:15:22 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/18 14:15:13 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	append_intersect(t_intersect **lst, double *xs, t_object *obj)
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

static void	intersect_cylinder(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[2];
	double	a;
	double	b;
	double	d;
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	a = ray_o[1][0] * ray_o[1][0] + ray_o[1][2] * ray_o[1][2];
	if (abs_f(a) < EPSILON)
		return ;
	b = 2 * (ray_o[0][0] * ray_o[1][0] + ray_o[0][2] * ray_o[1][2]);
	d = b * b - 4 * a * (ray_o[0][0] * ray_o[0][0] + ray_o[0][2] * ray_o[0][2] - 1);
	if (d < 0)
		return ;
	xs[0] = (-b - sqrt(d)) / (2 * a);
	xs[1] = (-b + sqrt(d)) / (2 * a);
	append_intersect(lst, xs, obj);
	free_ray(ray_o);
}

static void	intersect_sphere(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[2];
	double	*sp_to_ray;
	double	a;
	double	b;
	double	d;
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	sp_to_ray = vector(ray_o[0][0], ray_o[0][1], ray_o[0][2]);
	a = dot_product(ray_o[1], ray_o[1]);
	b = 2 * dot_product(ray_o[1], sp_to_ray);
	d = b * b - 4 * a * (dot_product(sp_to_ray, sp_to_ray) - 1);
	if (d < 0)
		return ;
	xs[0] = (-b - sqrt(d)) / (2 * a);
	xs[1] = (-b + sqrt(d)) / (2 * a);
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
		return ;
	xs[0] = - ray_o[0][1] / ray_o[1][1];
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
