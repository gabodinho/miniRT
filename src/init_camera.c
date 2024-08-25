/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:33:21 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 22:13:26 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
from is the cameras view point;
forward is the cameras normalized orientation vector;
up is a vector pointing in the 'up' direction;
*/
static double	*view_transform(double *from, double *forward, double *up)
{
	double	*left;
	double	*true_up;
	double	*orientation;
	double	*trans;

	normalize(up);
	left = cross_product(forward, up);
	true_up = cross_product(left, forward);
	orientation = identity_matrix(4);
	orientation[m2a(4, 0, 0)] = left[0];
	orientation[m2a(4, 0, 1)] = left[1];
	orientation[m2a(4, 0, 2)] = left[2];
	orientation[m2a(4, 1, 0)] = true_up[0];
	orientation[m2a(4, 1, 1)] = true_up[1];
	orientation[m2a(4, 1, 2)] = true_up[2];
	orientation[m2a(4, 2, 0)] = -forward[0];
	orientation[m2a(4, 2, 1)] = -forward[1];
	orientation[m2a(4, 2, 2)] = -forward[2];
	trans = translate(-from[0], -from[1], -from[2]);
	free(true_up);
	true_up = mat_mat_prod(orientation, trans);
	free(left);
	free(orientation);
	free(trans);
	return (true_up);
}

static void	calc_pixel_size(t_camera *cam)
{
	double	aspect;
	double	half_view;

	half_view = tan(cam -> field_of_view / 180 * M_PI / 2);
	aspect = HSIZE / VSIZE;
	if (aspect >= 1)
	{
		cam -> half_height = half_view / aspect;
		cam -> half_width = half_view;
	}
	else
	{
		cam -> half_width = half_view * aspect;
		cam -> half_height = half_view;
	}
	cam -> pixel_size = cam -> half_width * 2 / HSIZE;
	// printf("pixel size: %f\n", cam -> pixel_size);
}

t_camera	*init_camera(char *input)
{
	t_camera	*cam;
	double		*up;

	cam = malloc(sizeof(t_camera));
	// include malloc protection
	input += 1 + skip_empty(input + 1);
	cam -> view_p = get_double_touple(&input, 0);
	cam -> norm_v = get_double_touple(&input, 1);
	get_double(&cam -> field_of_view, input);
	calc_pixel_size(cam);
	up = vector(0, 1, 0);
	// keep in mind that program cannot compute inv_mat when norm vector (0,y,0)
	cam -> transform = view_transform(cam -> view_p, cam -> norm_v, up);
	cam -> inv_trans = invert(cam -> transform, 4);
	free(up);
	return (cam);
}
