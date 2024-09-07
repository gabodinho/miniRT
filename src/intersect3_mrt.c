/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect3_mrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shola_linux <shola_linux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:48:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/07 16:28:07 by shola_linux      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (!check_cap(ray, xs[0]))
		xs[0] = -1;
	xs[1] = (0.5 - ray[0][1]) / ray[1][1];
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

void	intersect_cylinder(double **ray, t_object *obj, t_intersect **lst)
{
	double	xs[4];
	double	temp[3];
	double	**ray_o;

	ray_o = transform(ray, obj -> inv_trans);
	temp[0] = ray_o[1][0] * ray_o[1][0] + ray_o[1][2] * ray_o[1][2];
	if (temp[0] < EPSILON)
	{
		intersect_caps(xs, ray_o, 1);
		append_intersect(lst, xs, obj);
		return ;
	}
	temp[1] = 2 * (ray_o[0][0] * ray_o[1][0] + ray_o[0][2] * ray_o[1][2]);
	temp[2] = temp[1] * temp[1] - 4 * temp[0]
		* (ray_o[0][0] * ray_o[0][0] + ray_o[0][2] * ray_o[0][2] - 1);
	if (temp[2] < 0)
	{
		free_ray(ray_o);
		return ;
	}
	xs[0] = (-temp[1] - sqrt(temp[2])) / (2 * temp[0]);
	xs[1] = (-temp[1] + sqrt(temp[2])) / (2 * temp[0]);
	intersect_caps(xs + 2, ray_o, 0);
	check_intersects(xs, ray_o);
	append_intersect(lst, xs, obj);
}
