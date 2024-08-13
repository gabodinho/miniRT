/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:15:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/13 20:20:05 by gabodinho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector(double a, double b, double c)
{
	double	*vector;

	vector = malloc(sizeof(double) * 4);
	// create error message
	if (!vector)
		return (0);
	vector[0] = a;
	vector[1] = b;
	vector[2] = c;
	vector[3] = 0;
	return (vector);
}

double	*point(double a, double b, double c)
{
	double	*point;

	point = malloc(sizeof(double) * 4);
	// create error message
	if (!point)
		return (0);
	point[0] = a;
	point[1] = b;
	point[2] = c;
	point[3] = 1;
	return (point);
}

void	normalize(double tuple[4])
{
	double	length;
	int		i;

	length = sqrt(tuple[0]*tuple[0] + tuple[1]*tuple[1] + tuple[2]*tuple[2]);
	i = -1;
	while (++i < 4)
		tuple[i] = tuple[i] / length;
}

double	dot_product(double *v1, double *v2)
{
	if (v1[3] || v2[3])
	{
		printf("only vectors are allowed!\n");
		return (-1);
	}
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

double	*cross_product(double *v1, double *v2)
{
	double	a;
	double	b;
	double	c;

	if (v1[3] || v2[3])
	{
		printf("only vectors are allowed!\n");
		return (NULL);
	}
	a = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	b = v1[2] * v2[0] - v1[0] * v2[2];
	c = v1[0] * v2[1] - v1[1] * v2[0];
	return (vector(a, b, c));
}

static int	mat2arr(int size_j, int i, int j)
{
	return (i * size_j + j);
}

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
		mat[mat2arr(size, i, i)] = 1;
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
			temp = m[mat2arr(size, i, j)];
			m[mat2arr(size, i, j)] = m[mat2arr(size, j, i)];
			m[mat2arr(size, j, i)] = temp;
		}
	}
}

double	det2x2(double *m)
{
	return (m[0] * m[3] - m[1] * m[2]);
}

double	*submatrix(double *m, int size, int row, int col)
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
				*res++ = m[mat2arr(size, i, j)];
		}
	}
	return (ptr);
}