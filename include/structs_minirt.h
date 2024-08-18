/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_minirt.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:29:30 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/18 15:10:50 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MRT_H
# define STRUCTS_MRT_H
# include <stdbool.h>
# include "ft_printf.h"
# define EPSILON 0.001
# define HSIZE 401.00
# define VSIZE 301.00
# define DIFFUSE 0.9
# define SPECULAR 0.9
# define SHINE 150

typedef enum e_shape
{
	SPHERE,
	PLANE,
	CYLNDR
}	t_shape;


/*
geometric, positional and material properties;
not all values for all shapes!
colour vetors are being set up during initialisation: rgb val / 255
*/
typedef struct s_object
{
	t_shape		shape;
	double*		point;
	double*		n_vec;
	double		diam;
	double		height;
	double*		transform;
	double*		inv_trans;
	double	*colour;
}	t_object;

/*
t: intersection value;
obj: respective object
*/
typedef struct s_intersect
{
	double				t;
	t_object			*obj;
	struct s_intersect	*next;
}	t_intersect;

/*
world contains an array of all the objects and the light information.
colour vetors are being set up during initialisation: rgb val / 255
amb_colour = amb_colour * ambient_intensity.
*/
typedef struct s_world
{
	t_object	**objects;
	int			n_obj;
	double		*light_point;
	double		light_bright;
	double		*amb_colour;
}	t_world;

/*
contains necessary values for shading computation:
point_w: point in world coordinates where hit occured;
eye_vec: vector towards camera from hit;
normal_vec: normalized surface normal vector at hit;
inside: true if inside of body;
obj: object vector;
*/
typedef struct s_comps
{
	double		*point_w;
	double		*eye_vec;
	double		*normal_vec;
	bool		inside;
	t_object	*obj;
}	t_comps;

typedef struct s_camera
{
	double	vp_x;
	double	vp_y;
	double	vp_z;
	double	nv_x;
	double	nv_y;
	double	nv_z;
	double	field_of_view;
	double	*transform;
	double	*inv_trans;
	double	half_width;
	double	half_height;
	double	pixel_size;
}	t_camera;

#endif
