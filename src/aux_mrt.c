/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:58:36 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/16 01:31:16 by ggiertzu         ###   ########.fr       */
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

void	free_ray(double **ray)
{
	free(ray[0]);
	free(ray[1]);
	free(ray);
}
