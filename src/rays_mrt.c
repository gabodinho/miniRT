/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:19:41 by gabodinho         #+#    #+#             */
/*   Updated: 2024/08/17 20:22:55 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**ray(double *origin, double *direction)
{
	double	**ray;

	ray = malloc(sizeof(double *) * 2);
	// throw errror
	if (!ray)
		return (NULL);
	ray[0] = origin;
	ray[1] = direction;
	return (ray);
}

double	*position(double **ray, double t)
{
	return (point(
	ray[0][0] + t * ray[1][0],
	ray[0][1] + t * ray[1][1],
	ray[0][2] + t * ray[1][2]));
}



