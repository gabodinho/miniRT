/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:15:08 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/13 15:57:09 by gabodinho        ###   ########.fr       */
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