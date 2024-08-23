/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_mrt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:15:22 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/24 00:20:04 by ggiertzu         ###   ########.fr       */
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

static int	check_cap(double **ray, double t)
{
	double	*pos;
	double	res;

	pos = position(ray, t);
	res = 0;
	if ((pos[0] * pos[0]) + (pos[2] * pos[2]) <= 1)
		res = 1;
	free(pos);
	return (res);
}

static void	intersect_caps(double *xs, double **ray, int del_ray)
{
	if (abs_f(ray[1][1]) < EPSILON)
	{
		xs[0] = -1;
		xs[1] = -1;
		if (del_ray)
			free_ray(ray);
		return ;
	}
	xs[0] = (-0.5 - ray[0][1]) / ray[1][1];
	// check lower cap
	if (!check_cap(ray, xs[0]))
		xs[0] = -1;
	xs[1] = (0.5 - ray[0][1]) / ray[1][1];
	// check upper cap
	if (!check_cap(ray, xs[1]))
		xs[1] = -1;
	if (del_ray)
		free_ray(ray);
}

static double	find_cap_hit(double *xs)
{
	double	temp;

	if (xs[2] != -1)
	{
		temp = xs[2];
		xs[2] = -1;
		return (temp);
	}
	else
	{
		temp = xs[3];
		xs[3] = -1;
		return (temp);
	}
}

static void	check_intersects(double xs[4], double **ray)
{
	double	*pos;

	pos = position(ray, xs[0]);
	if (pos[1] > 0.5 || pos[1] < -0.5)
		xs[0] = find_cap_hit(xs);
	free(pos);
	pos = position(ray, xs[1]);
	if (pos[1] > 0.5 || pos[1] < -0.5)
		xs[1] = find_cap_hit(xs);
	free(pos);
	free_ray(ray);
}

static void	intersect_cylinder(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[4];
	double	a;
	double	b;
	double	d;
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	a = ray_o[1][0] * ray_o[1][0] + ray_o[1][2] * ray_o[1][2];
	// ray is collinear with cylinder and thus doesnt intersect the sides
	if (a < EPSILON)
	{
		intersect_caps(xs, ray_o, 1);
		append_intersect(lst, xs, obj);
		return ;
	}
	b = 2 * (ray_o[0][0] * ray_o[1][0] + ray_o[0][2] * ray_o[1][2]);
	d = b * b - 4 * a * (ray_o[0][0] * ray_o[0][0] + ray_o[0][2] * ray_o[0][2] - 1);
	// ray doesnt intersect neither side nor caps
	if (d < 0)
	{
		free_ray(ray_o);
		return ;
	}
	xs[0] = (-b - sqrt(d)) / (2 * a);
	xs[1] = (-b + sqrt(d)) / (2 * a);
	intersect_caps(xs + 2, ray_o, 0);
	// printf("Axs: %.2f, %.2f, %.2f, %.2f ", xs[0], xs[1], xs[2], xs[3]);
	check_intersects(xs, ray_o);
	// printf("Bxs: %.2f, %.2f, %.2f, %.2f\n", xs[0], xs[1], xs[2], xs[3]);
	append_intersect(lst, xs, obj);
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
	{
		free_ray(ray_o);
		return ;
	}
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
