/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_mrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:15:46 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 12:55:56 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static double	*get_ambient(double *eff_col, t_world *w)
{
	hadamard_prod(eff_col, w -> amb_colour);
	return (eff_col);
}

static double	*get_diffuse(double *eff_col, double *light_v, t_comps *comps)
{
	double	*diffuse;
	double	light_dot_norm;

	normalize(light_v);
	light_dot_norm = dot_product(light_v, comps -> norm_v);
	if (light_dot_norm < 0)
		diffuse = point(0, 0, 0);
	else
	{
		diffuse = copy_vec(eff_col, 3);
		vec_skal_prod(diffuse, DIFFUSE * light_dot_norm, 3);
	}
	free(light_v);
	return (diffuse);
}

static double	*get_specular(double *light_v, t_comps *comps, t_world *w)
{
	double	*reflect_v;
	double	temp;
	double	*specular;

	normalize(light_v);
	if (dot_product(light_v, comps -> norm_v) < 0)
		specular = point(0, 0, 0);
	else
	{
		vec_skal_prod(light_v, -1, 3);
		reflect_v = reflect(light_v, comps -> norm_v);
		if (dot_product(reflect_v, comps -> eye_v) <= 0)
			specular = point(0, 0, 0);
		else
		{
			temp = w -> light_bright * SPECULAR
				* pow(dot_product(reflect_v, comps -> eye_v), SHINE);
			specular = point(temp, temp, temp);
		}
		free(reflect_v);
	}
	free(light_v);
	return (specular);
}

static void	add_three_col(double *c1, double *c2, double *c3)
{
	int	i;

	i = -1;
	while (++i < 3)
		c1[i] += c2[i] + c3[i];
}

double	*lighting(t_world *w, t_comps *comps)
{
	t_object	*obj;
	double		*eff_col;
	double		*ambient;
	double		*diffuse;
	double		*specular;

	obj = comps -> obj;
	eff_col = point(obj -> colour[0], obj -> colour[1], obj -> colour[2]);
	vec_skal_prod(eff_col, w -> light_bright, 3);
	ambient = get_ambient(copy_vec(eff_col, 3), w);
	if (is_shadowed(w, comps -> over_p))
		return (ambient);
	diffuse = get_diffuse(eff_col,
		substract_points(w -> light_p, comps -> world_p), comps);
	specular = get_specular(
		substract_points(w -> light_p, comps -> world_p), comps, w);
	add_three_col(ambient, diffuse, specular);
	free(diffuse);
	free(specular);
	return (ambient);
}
