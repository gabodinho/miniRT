/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 22:05:51 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_plane_trans(t_object *pl)
{
	double	*rot_x_;
	double	*rot_y_;
	double	*translate_;
	double	*temp;

	// rot_x_ = rot_x(acos(pl -> norm_v[1]));
	// rot_y_ = rot_y(acos(pl -> norm_v[2]));
	if (pl -> norm_v[2] >= 0)
		rot_x_ = rot_x(acos(pl -> norm_v[1]));
	else
		rot_x_ = rot_x(-acos(pl -> norm_v[1]));
	if (pl -> norm_v[0] >= 0)
		rot_y_ = rot_y(acos(pl -> norm_v[2]));
	else
		rot_y_ = rot_y(-acos(pl -> norm_v[2]));
	translate_ = translate(pl -> obj_p[0], pl -> obj_p[1], pl -> obj_p[2]);
	temp = mat_mat_prod(rot_y_, rot_x_);
	pl -> transform = mat_mat_prod(translate_, temp);
	free(rot_x_);
	free(rot_y_);
	free(translate_);
	free(temp);
}

/* input is str starting at first non empty char after pl identifier */
t_object	*init_plane(char *input)
{
	t_object	*plane;

	plane = create_empty_obj();
	plane -> shape = PLANE;
	input += 2 + skip_empty(input + 2);
	plane -> obj_p = get_double_touple(&input, 0);
	plane -> norm_v = get_double_touple(&input, 1);
	plane -> colour = get_double_touple(&input, 2);
	set_plane_trans(plane);
	plane -> inv_trans = invert(plane -> transform, 4);
	return (plane);
}
