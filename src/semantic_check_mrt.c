/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_check_mrt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:39:36 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 18:40:23 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_obj_bounds(t_object *obj)
{
	int		i;
	double	a;

	i = -1;
	a = 0;
	while (++i < 3)
	{
		if (obj -> norm_v)
			a += pow(obj -> norm_v[i], 2);
		if (obj -> colour[i] < 0 || obj -> colour[i] > 1)
			return (print_error(3, "object colour out of bounds\n"));
	}
	if (obj -> norm_v && (sqrt(a) < 0.99 || sqrt(a) > 1.01))
		return (print_error(3, "object normal vector out of bounds\n"));
	if (obj -> diam < 0 || obj -> height < 0)
		return (print_error(3, "object height/diameter out of bounds\n"));
	return (0);
}

static int	check_cam_light_bounds(t_world *w)
{
	int		i;
	double	a;

	i = -1;
	a = 0;
	while (++i < 3)
	{
		a += pow(w -> cam -> norm_v[i], 2);
		if (w ->amb_colour[i] < 0 || w -> amb_colour[i] > 1)
			return (print_error(3, "ambient colour out of bounds\n"));
	}
	if (sqrt(a) < 0.99 || sqrt(a) > 1.01)
		return (print_error(3, "camera normal vector out of bounds\n"));
	if (w -> light_bright < 0 || w -> light_bright > 1
	|| w -> amb_ratio < 0 || w -> amb_ratio > 1)
		return (print_error(3, "light_bright/ambient_ratio out of bounds\n"));
	if (w -> cam -> field_of_view < 0 || w -> cam -> field_of_view > 180)
		return (print_error(3, "camera field of view out of bounds\n"));
	return (0);
}

static int	check_boundaries(t_world *w)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (++i < w -> n_obj)
		res |= check_obj_bounds(w -> objects[i]);
	res |= check_cam_light_bounds(w);
	return (res);
}

int	semantic_check(t_world *w)
{
	char	*str;

	str = NULL;
	if (!w -> cam)
		str = "no camera\n";
	else if (!w -> light_p)
		str = "no light source\n";
	else if (!w -> amb_colour)
		str = "no ambient light specified\n";
	if (str)
	{
		clean_up(w);
		return (print_error(3, str));
	}
	else if (check_boundaries(w))
		return (3);
	return (0);
}
