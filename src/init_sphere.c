/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:39:37 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/28 01:35:25 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_sphere_trans(t_object *sp)
{
	double	*scale_;
	double	*translate_;

	scale_ = scale(sp -> diam / 2, sp -> diam / 2, sp -> diam / 2);
	translate_ = translate(sp -> obj_p[0], sp -> obj_p[1], sp -> obj_p[2]);
	sp -> transform = mat_mat_prod(translate_, scale_);
	free(scale_);
	free(translate_);
}

t_object	*init_sphere(char *input)
{
	t_object	*sphere;

	sphere = create_empty_obj();
	sphere -> shape = SPHERE;
	input += 2 + skip_empty(input + 2);
	sphere -> obj_p = get_double_touple(&input, 0);
	input += get_double(&sphere -> diam, input);
	while (*input == ' ')
		input++;
	sphere -> colour = get_double_touple(&input, 2);
	set_sphere_trans(sphere);
	sphere -> inv_trans = invert(sphere -> transform, 4);
	sphere -> norm_v = point(0, 0, 0);
	return (sphere);
}
