/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/10 19:25:49 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_plane_trans(t_object *pl)
{
	double	*m_rot;
	double	*translate_;

	m_rot = get_rot_mat(pl -> norm_v);
	translate_ = translate(pl -> obj_p[0], pl -> obj_p[1], pl -> obj_p[2]);
	pl -> transform = mat_mat_prod(translate_, m_rot);
	free(m_rot);
	free(translate_);
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
