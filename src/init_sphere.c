/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:39:37 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/23 11:20:34 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_sphere_trans(t_object *sp)
{
	double	*scale_;
	double	*translate_;

	scale_ = scale(sp -> diam / 2, sp -> diam / 2, sp -> diam / 2);
	translate_ = translate(sp -> point[0], sp -> point[1], sp -> point[2]);
	printf("translate: \n");
	print_vec(translate_, 4);
	sp -> transform = mat_mat_prod(translate_, scale_, 4);
	free(scale_);
	free(translate_);
	printf("trafo: \n");
	print_vec(sp -> transform, 4);
}

t_object	*init_sphere(char *inspt)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	sphere -> shape = SPHERE;
	sphere -> point = get_double_touple(&inspt, 0);
	inspt += get_double(&sphere -> diam, inspt);
	while (*inspt == ' ')
		inspt++;
	sphere -> colour = get_double_touple(&inspt, 2);
	set_sphere_trans(sphere);
	sphere -> inv_trans = invert(sphere -> transform, 4);
	return (sphere);
}
