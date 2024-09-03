/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_minirt.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:29:30 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/03 19:40:12 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MINIRT_H
# define STRUCTS_MINIRT_H
# include <stdbool.h>
# include "ft_printf.h"
# define EPSILON 0.001
# define HSIZE 401.00
# define VSIZE 301.00
# define DIFFUSE 0.9
# define SPECULAR 0.9
# define SHINE 200.0

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
typedef struct s_object	// free
{
	t_shape	shape;
	double	*obj_p;		// free
	double	*norm_v;	// free
	double	diam;
	double	height;
	double	*transform;	// free
	double	*inv_trans;	// free
	double	*colour;	// free
}	t_object;

/*
t: intersection value;
obj: respective object
*/
typedef struct s_intersect	// free
{
	double				t;
	t_object			*obj;	// free
	struct s_intersect	*next;
}	t_intersect;

typedef struct s_camera
{
	double	*view_p;	// free
	double	*norm_v;	// free
	double	field_of_view;
	double	*transform;	// free
	double	*inv_trans;	// free
	double	half_width;
	double	half_height;
	double	pixel_size;
}	t_camera;

/*
world contains an array of all the objects and the light information.
colour vetors are being set up during initialisation: rgb val / 255
amb_colour = amb_colour * ambient_intensity.
*/
typedef struct s_world	// free
{
	t_object	**objects;	// free free
	int			n_obj;
	double		*light_p;	// free
	double		light_bright;
	double		*amb_colour;	// free
	t_camera	*cam;
}	t_world;

/*
contains necessary values for shading computation:
point_w: point in world coordinates where hit occured;
eye_vec: vector towards camera from hit;
normal_vec: normalized surface normal vector at hit;
inside: true if inside of body;
obj: object vector;
*/
typedef struct s_comps		// free
{
	double		*world_p;	// free
	double		*over_p;	// free
	double		*eye_v;		// free
	double		*norm_v;	// free
	bool		inside;
	t_object	*obj;
}	t_comps;

#endif
