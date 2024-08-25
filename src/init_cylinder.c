/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 13:01:12 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_cylinder_trans(t_object *cyl)
{
	double	*rot_x_;
	double	*rot_y_;
	double	*translate_;
	double	*scale_;
	double	**temp;

	rot_x_ = rot_x(acos(cyl -> norm_v[1]));
	printf("rot_x: \n");
	print_vec(rot_x_, 4);
	rot_y_ = rot_y(acos(cyl -> norm_v[2]));
	printf("rot_y: \n");
	print_vec(rot_y_, 4);
	translate_ = translate(cyl -> obj_p[0], cyl -> obj_p[1], cyl -> obj_p[2]);
	printf("translate: \n");
	print_vec(translate_, 4);
	scale_ = scale(cyl -> diam / 2, cyl -> height, cyl -> diam / 2);
	printf("scale: \n");
	print_vec(scale_, 4);
	temp = malloc(sizeof(double *) * 2);
	temp[0] = mat_mat_prod(translate_, rot_y_, 4);
	temp[1] = mat_mat_prod(temp[0], rot_x_, 4);
	cyl -> transform = mat_mat_prod(temp[1], scale_, 4);
	free(rot_x_);
	free(rot_y_);
	free(translate_);
	free_ray(temp);
}

/* input is str starting at first non empty char after cy identifier */
t_object	*init_cylinder(char *input)
{
	t_object	*cyl;

	cyl = malloc(sizeof(t_object));
	cyl -> shape = CYLNDR;
	cyl -> obj_p = get_double_touple(&input, 0);
	cyl -> norm_v = get_double_touple(&input, 1);
	input += get_double(&cyl -> diam, input);
	while (*input == ' ')
		input++;
	input += get_double(&cyl -> height, input);
	while (*input == ' ')
		input++;
	cyl -> colour = get_double_touple(&input, 2);
	set_cylinder_trans(cyl);
	cyl -> inv_trans = invert(cyl -> transform, 4);
	return (cyl);
}
