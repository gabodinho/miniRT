/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shola_linux <shola_linux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:15:15 by gabodinho         #+#    #+#             */
/*   Updated: 2024/09/07 16:28:58 by shola_linux      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	det2x2(double *m)
{
	return (m[0] * m[3] - m[1] * m[2]);
}

static double	*submatrix(double *m, int size, int row, int col)
{
	double	*res;
	double	*ptr;
	int		i;
	int		j;

	if (size <= 1)
		return (m);
	res = malloc(sizeof(double) * (size - 1) * (size - 1));
	ptr = res;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (i != row && j != col)
				*res++ = m[m2a(size, i, j)];
		}
	}
	return (ptr);
}

static double	cofactor(double *m, int size, int i, int j)
{
	double	*temp;
	double	res;
	int		k;

	if (size == 3)
	{
		temp = submatrix(m, 3, i, j);
		res = det2x2(temp);
		free(temp);
		if ((i + j) % 2 == 1)
			return (-res);
		return (res);
	}
	res = 0;
	k = -1;
	while (++k < 3)
	{
		temp = submatrix(m, 4, i, j);
		res += temp[m2a(3, 0, k)] * cofactor(temp, 3, 0, k);
		free(temp);
	}
	if ((i + j) % 2 == 1)
		return (-res);
	return (res);
}

static double	determinant(double *m, int size)
{
	int		i;
	double	res;

	i = -1;
	res = 0;
	while (++i < size)
		res += cofactor(m, size, 0, i) * m[m2a(size, 0, i)];
	return (res);
}

double	*invert(double *m, int size)
{
	int		i;
	int		j;
	double	*res;
	double	det;

	det = determinant(m, size);
	if (!det)
		return (NULL);
	res = malloc(sizeof(double) * size * size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			res[m2a(4, i, j)] = cofactor(m, 4, j, i) / det;
	}
	return (res);
}
