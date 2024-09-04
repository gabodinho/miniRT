/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/04 22:35:29 by gabodinho        ###   ########.fr       */
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
	rot_y_ = rot_y(acos(cyl -> norm_v[2]));
	translate_ = translate(cyl -> obj_p[0], cyl -> obj_p[1], cyl -> obj_p[2]);
	scale_ = scale(cyl -> diam / 2, cyl -> height, cyl -> diam / 2);
	temp = malloc(sizeof(double *) * 2);
	temp[0] = mat_mat_prod(translate_, rot_y_);
	temp[1] = mat_mat_prod(temp[0], rot_x_);
	cyl -> transform = mat_mat_prod(temp[1], scale_);
	free(rot_x_);
	free(rot_y_);
	free(translate_);
	free(scale_);
	free_ray(temp);
}

t_object	*create_empty_obj(void)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		perror("create_empty_obj");
		exit(1);
	}
	obj -> colour = NULL;
	obj -> inv_trans = NULL;
	obj -> norm_v = NULL;
	obj -> obj_p = NULL;
	obj -> transform = NULL;
	obj -> diam = 0;
	return (obj);
}

/* input is str starting at first non empty char after cy identifier */
t_object	*init_cylinder(char *input)
{
	t_object	*cyl;

	cyl = create_empty_obj();
	cyl -> shape = CYLNDR;
	input += 2 + skip_empty(input + 2);
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
