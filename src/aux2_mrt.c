/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shola_linux <shola_linux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:45:06 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/07 19:37:10 by shola_linux      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_comps(t_comps *comps)
{
	free(comps -> world_p);
	free(comps -> norm_v);
	free(comps -> eye_v);
	free(comps -> over_p);
	free(comps);
}

void	free_intersect(t_intersect *xs)
{
	t_intersect	*ptr;

	ptr = xs;
	while (xs)
	{
		ptr = xs;
		xs = xs -> next;
		free(ptr);
	}
}

void	free_ray(double **ray)
{
	free(ray[0]);
	free(ray[1]);
	free(ray);
}

int	m2a(int size_j, int i, int j)
{
	return (i * size_j + j);
}
