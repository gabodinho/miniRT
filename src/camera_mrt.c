/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:33:21 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/17 20:05:20 by ggiertzu         ###   ########.fr       */
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
	true_up = mat_mat_prod(orientation, trans, 4);
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

/*
values for camera position, direction vector and field_of_view
have already been assigned at parsing level;
*/
void	init_camera(t_camera *cam)
{
	double	*from;
	double	*direction;
	double	*up;

	calc_pixel_size(cam);
	from = point(cam -> vp_x, cam -> vp_y, cam -> vp_z);
	direction = vector(cam -> nv_x, cam -> nv_y, cam -> nv_z);
	up = vector(0, 1, 0);
	cam -> transform = view_transform(from, direction, up);
	// printf("camera transform:\n");
	// print_vec(cam -> transform, 4);
	cam -> inv_trans = invert(cam -> transform, 4);
	free(from);
	free(direction);
	free(up);
}

double	**ray_for_pixel(t_camera *cam, int	x, int y)
{
	double	x_world;
	double	y_world;
	double	*pixel;
	double	*origin;
	double	*direction;
	double	**ray;

	x_world = cam -> half_width - ((x + 0.5) * cam -> pixel_size);
	y_world = cam -> half_height - ((y + 0.5) * cam -> pixel_size);
	ray = malloc(sizeof(double *) * 2);
	pixel = point(x_world, y_world, -1);
	origin = point(0, 0, 0);
	ray[0] = mat_vec_prod(cam -> inv_trans, origin);
	// printf("transformed origin: \n");
	// print_vec(ray[0], 0);
	// printf("transform matrix check:\n");
	// print_vec(mat_mat_prod(cam -> transform, cam -> inv_trans, 4), 4);
	ray[1] = mat_vec_prod(cam -> inv_trans, pixel);
	// printf("transformed pixel: \n");
	// print_vec(ray[1], 0);
	direction = substract_points(ray[1], ray[0]);
	normalize(direction);
	free(ray[1]);
	ray[1] = direction;
	free(pixel);
	free(origin);
	return (ray);
}

