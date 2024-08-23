/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:17:57 by gabodinho         #+#    #+#             */
/*   Updated: 2024/08/23 23:01:10 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*identity_matrix(int size)
{
	double	*mat;
	int		i;

	mat = malloc(sizeof(double) * size * size);
	// throw error
	if (!mat)
		return (NULL);
	ft_memset(mat, 0, size * size * sizeof(double));
	i = -1;
	while (++i < size)
		mat[m2a(size, i, i)] = 1;
	return (mat);
}

void	transpose(double *m, int size)
{
	double	temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			temp = m[m2a(size, i, j)];
			m[m2a(size, i, j)] = m[m2a(size, j, i)];
			m[m2a(size, j, i)] = temp;
		}
	}
}
static double	calc_val(double *m1, double *m2, int i, int j, int size)
{
	int		k;
	double	res;

	k = -1;
	res = 0;
	while (++k < size)
		res += m1[m2a(size, i, k)] * m2[m2a(size, k, j)];
	return (res);
}

/*
first arg: quadratic matrix of size x size;
second arg: quadratic matrix of size x size;
*/
double  *mat_mat_prod(double *m1, double *m2, int size)
{
	double	*res;
	int		i;
	int		j;

	res = malloc(sizeof(double) * size * size);
	i = -1;
	while(++i < size)
	{
		j = -1;
		while(++j < size)
			res[m2a(size, i, j)] = calc_val(m1, m2, i, j, size);
	}
	return (res);
}

/*
first arg: quadratic matrix of size 4 x 4;
second arg: vector of size 4 x 1;
*/
double  *mat_vec_prod(double *m, double *v)
{
	double	*res;
	int		i;
	int		j;

	res = malloc(sizeof(double) * 4);
	i = -1;
	while(++i < 4)
	{
		res[i] = 0;
		j = -1;
		while(++j < 4)
			res[i] += m[m2a(4, i, j)] * v[j];
	}
	return (res);
}
