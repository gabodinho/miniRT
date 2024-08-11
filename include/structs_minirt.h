/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_minirt.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:29:30 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/11 16:24:05 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MRT_H
# define STRUCTS_MRT_H

typedef enum e_shape
{
	SPHERE,
	PLANE,
	CYLNDR
}	t_shape;

// material properties regarding light reflection
typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shine;
}	t_material;

/*
geometric, positional and material properties;
not all values for all shapes!
*/
typedef struct s_object
{
	t_shape		shape;
	int			rgba;
	double*		point;
	double*		n_vec;
	double		diam;
	double		height;
	double**	transform;
	t_material	*material;
}	t_object;

/*
xs: intersection value;
obj: respective object
*/
typedef struct s_intersect
{
	double		t;
	t_object	*obj;
}	t_intersect;

/*
world contains an array of all the objects and the light information
*/
typedef struct s_world
{
	t_object	**obj_arr;
	double		*light_point;
	double		brightness;
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

#endif