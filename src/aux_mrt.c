/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shola_linux <shola_linux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:58:36 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/07 18:42:04 by shola_linux      ###   ########.fr       */
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
		v[i] = v[i] * s;
}

double	*copy_vec(double *v, int size)
{
	double	*res;
	int		i;

	res = malloc(sizeof(double) * size);
	i = -1;
	while (++i < size)
		res[i] = v[i];
	return (res);
}

double	*substract_points(double *a, double *b)
{
	double	*res;

	res = vector(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
	return (res);
}
