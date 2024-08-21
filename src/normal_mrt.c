/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:20:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/22 00:40:05 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	*cylinder_normal(t_object *obj, double *p_w)
{
	double	*n_o;
	double	*n_w;
	double	dist;
	double	*p_o;

	p_o = mat_vec_prod(obj -> inv_trans, p_w);
	dist = p_o[0] * p_o[0] + p_o[2] * p_o[2];
	if (dist < 1 && p_o[1] >= 1 - EPSILON)
		n_o = vector(0, 1, 0);
	else if (dist < 1 && p_o[1] <= 0 - EPSILON)
		n_o = vector(0, -1, 0);
	else
		n_o = vector(p_o[0], 0, p_o[2]);
	transpose(obj -> inv_trans, 4);
	n_w = mat_vec_prod(obj -> inv_trans, n_o);
	n_w[3] = 0;
	transpose(obj -> inv_trans, 4);
	normalize(n_w);
	free(n_o);
	free(p_o);
	return (n_w);
}

static double	*plane_normal(t_object *obj)
{
	double	*n_o;
	double	*n_w;

	n_o = vector(0, 1, 0);
	transpose(obj -> inv_trans, 4);
	n_w = mat_vec_prod(obj -> inv_trans, n_o);
	n_w[3] = 0;
	transpose(obj -> inv_trans, 4);
	normalize(n_w);
	free(n_o);
	return (n_w);
}

static double	*sphere_normal(t_object *obj, double *p_w)
{
	double	*n_o;
	double	*n_w;

	n_o = mat_vec_prod(obj -> inv_trans, p_w);
	n_o[3] = 0;
	transpose(obj -> inv_trans, 4);
	n_w = mat_vec_prod(obj -> inv_trans, n_o);
	n_w[3] = 0;
	transpose(obj -> inv_trans, 4);
	normalize(n_w);
	free(n_o);
	return (n_w);
}

double	*normal_at(t_object *obj, double *p_w)
{
	if (obj -> shape == SPHERE)
		return (sphere_normal(obj, p_w));
	else if (obj -> shape == CYLNDR)
		return (cylinder_normal(obj, p_w));
	else
		return (plane_normal(obj));
}

double	*reflect(double *in, double *normal)
{
	double	temp[3];
	double	*res;

	temp[0] = normal[0] * 2 * dot_product(in, normal);
	temp[1] = normal[1] * 2 * dot_product(in, normal);
	temp[2] = normal[2] * 2 * dot_product(in, normal);
	res = substract_points(in, temp);
	return (res);
}
