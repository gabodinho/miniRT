/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:58:36 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/18 02:36:56 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	abs_f(double val)
{
	if (val < 0)
		return (val * -1);
	else
		return (val);
}

void	free_comps(t_comps *comps)
{
	free(comps -> point_w);
	free(comps -> normal_vec);
	free(comps);
}

void	free_intersect(t_intersect *xs)
{
	t_intersect	*ptr;

	ptr = xs;
	while (xs)
	{
		ptr = xs;
		xs = xs -> next;
		free(ptr);
	}
}

void	free_ray(double **ray)
{
	free(ray[0]);
	free(ray[1]);
	free(ray);
}
/*
no free necessary for the result;
*/
void	hadamard_prod(double *c1, double *c2)
{
	c1[0] = c1[0] * c2[0];
	c1[1] = c1[1] * c2[1];
	c1[2] = c1[2] * c2[2];
}

void	vec_skal_prod(double *v, double s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		v[i] = v[0] * s;
}

double	*copy_vec(double *v, int size)
{
	double	*res;
	int		i;

	res = malloc(sizeof(double) * size);
	i = -1;
	while(++i < size)
		res[i] = v[i];
	return (res);
}
