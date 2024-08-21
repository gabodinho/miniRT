/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:15:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/21 20:43:53 by ggiertzu         ###   ########.fr       */
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
	while (++i < 3)
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
	b = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	c = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	return (vector(a, b, c));
}


