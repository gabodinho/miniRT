/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/10 18:10:47 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_cylinder_trans(t_object *cyl)
{
	double	*m_rot;
	double	*translate_;
	double	*scale_;
	double	*temp;

	m_rot = get_rot_mat(cyl -> norm_v);
	translate_ = translate(cyl -> obj_p[0], cyl -> obj_p[1], cyl -> obj_p[2]);
	scale_ = scale(cyl -> diam / 2, cyl -> height, cyl -> diam / 2);
	temp = mat_mat_prod(translate_, m_rot);
	cyl -> transform = mat_mat_prod(temp, scale_);
	free(m_rot);
	free(translate_);
	free(scale_);
	free(temp);
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
	obj -> height = 0;
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
