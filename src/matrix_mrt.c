/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:17:57 by gabodinho         #+#    #+#             */
/*   Updated: 2024/08/14 19:24:42 by gabodinho        ###   ########.fr       */
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
	ft_memset(mat, 0, size * size);
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

double	*translate(double x, double y, double z)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 0, 3)] = x;
	m[m2a(4, 1, 3)] = y;
	m[m2a(4, 2, 3)] = z;
	return (m);
}

double	*scale(double f)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 0, 0)] = f;
	m[m2a(4, 1, 1)] = f;
	m[m2a(4, 2, 2)] = f;
	return (m);
}

double	*rot_x(double phi)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 1, 1)] = cos(phi);
	m[m2a(4, 2, 2)] = cos(phi);
	m[m2a(4, 1, 2)] = -sin(phi);
	m[m2a(4, 2, 1)] = sin(phi);
	return (m);
}

double	*rot_y(double phi)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 0, 0)] = cos(phi);
	m[m2a(4, 2, 2)] = cos(phi);
	m[m2a(4, 0, 2)] = sin(phi);
	m[m2a(4, 2, 0)] = -sin(phi);
	return (m);
}

double	*rot_z(double phi)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 0, 0)] = cos(phi);
	m[m2a(4, 1, 1)] = cos(phi);
	m[m2a(4, 0, 1)] = -sin(phi);
	m[m2a(4, 1, 0)] = sin(phi);
	return (m);
}