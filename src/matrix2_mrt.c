/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2_mrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:36:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/16 01:38:04 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
