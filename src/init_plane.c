/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:26:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 13:01:12 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_double(double *f, char *str)
{
	int	i;
	int	len_dec;
	double	temp;

	i = 0;
	len_dec = 0;
	*f = (double) ft_atoi(str);
	while(!ft_strchr(", .\n", str[i]))
		i++;
	if (str[i] == ',')
		return (i + 1);
	else if (str[i] == '\n' || str[i] == ' ')
		return (i);
	else
		i++;
	temp = (double) (ft_atoi(str + i));
	while(!ft_strchr(", \n", str[i + len_dec]))
		len_dec++;
	*f += temp / pow(10, len_dec);
	if (*f < 1 && *f > 0 && *str == '-')
		*f *= -1;
	if (str[i + len_dec] == ',')
		return (i + len_dec + 1);
	else
		return (i + len_dec);
}

double	*get_double_touple(char **str, int kind)
{
	double	temp[3];
	int		i;

	i = -1;
	while(++i < 3)
		*str += get_double(temp + i, *str);
	while(**str == ' ')
		*str += 1;
	if (kind == 0)
		return (point(temp[0], temp[1], temp[2]));
	else if (kind == 1)
		return (vector(temp[0], temp[1], temp[2]));
	else
		return (point(temp[0] / 255.0, temp[1] / 255.0, temp[2] / 255.0));
}

static void	set_plane_trans(t_object *pl)
{
	double	*rot_x_;
	double	*rot_y_;
	double	*translate_;
	double	*temp;

	rot_x_ = rot_x(acos(pl -> norm_v[1]));
	// printf("rot_x: \n");
	// print_vec(rot_x_, 4);
	rot_y_ = rot_y(acos(pl -> norm_v[2]));
	// printf("rot_y: \n");
	// print_vec(rot_y_, 4);
	translate_ = translate(pl -> obj_p[0], pl -> obj_p[1], pl -> obj_p[2]);
	// printf("translate: \n");
	// print_vec(translate_, 4);
	temp = mat_mat_prod(rot_y_, rot_x_, 4);
	pl -> transform = mat_mat_prod(translate_, temp, 4);
	free(rot_x_);
	free(rot_y_);
	free(translate_);
	free(temp);
	// printf("trafo: \n");
	// print_vec(pl -> transform, 4);
}

/* input is str starting at first non empty char after pl identifier */
t_object	*init_plane(char *input)
{
	t_object	*plane;

	plane = malloc(sizeof(t_object));
	plane -> shape = PLANE;
	plane -> obj_p = get_double_touple(&input, 0);
	plane -> norm_v = get_double_touple(&input, 1);
	plane -> colour = get_double_touple(&input, 2);
	set_plane_trans(plane);
	plane -> inv_trans = invert(plane -> transform, 4);
	return (plane);
}
