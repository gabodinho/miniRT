/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2_mrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:36:09 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/10 19:22:57 by ggiertzu         ###   ########.fr       */
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

double	*scale(double x, double y, double z)
{
	double	*m;

	m = identity_matrix(4);
	m[m2a(4, 0, 0)] = x;
	m[m2a(4, 1, 1)] = y;
	m[m2a(4, 2, 2)] = z;
	return (m);
}

static void	add_mat(double *a, double *b)
{
	int	i;

	i = -1;
	while (++i < 16)
		a[i] += b[i];
}

static double	**get_skew_mat(double *r)
{
	double	**k;

	k = malloc(sizeof(double *) * 2);
	k[0] = malloc(sizeof(double) * 16);
	k[1] = malloc(sizeof(double) * 16);
	ft_memset(k[0], 0, 16 * sizeof(double));
	ft_memset(k[1], 0, 16 * sizeof(double));
	k[0][m2a(4, 0, 1)] = -r[2];
	k[0][m2a(4, 1, 0)] = r[2];
	k[0][m2a(4, 1, 2)] = -r[0];
	k[0][m2a(4, 2, 1)] = r[0];
	k[1] = mat_mat_prod(k[0], k[0]);
	return (k);
}

double	*get_rot_mat(double *nv)
{
	double	**k;
	double	*r;
	double	*m_rot;

	if (acos(nv[1]) == 0)
		return (identity_matrix(4));
	else if (acos(nv[1]) == M_PI)
		r = vector(1, 0, 0);
	else
		r = vector(nv[2], 0, -nv[0]);
	normalize(r);
	k = get_skew_mat(r);
	vec_skal_prod(k[0], sin(acos(nv[1])), 16);
	vec_skal_prod(k[1], 1 - nv[1], 16);
	m_rot = identity_matrix(4);
	add_mat(m_rot, k[0]);
	add_mat(m_rot, k[1]);
	free(r);
	free_ray(k);
	return (m_rot);
}
