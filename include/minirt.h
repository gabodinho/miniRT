/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:16:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/16 01:39:48 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"
#include "structs_minirt.h"

double	*vector(double a, double b, double c);
double	*point(double a, double b, double c);
void	normalize(double tuple[4]);
double	dot_product(double *v1, double *v2);
double	*cross_product(double *v1, double *v2);
double	*identity_matrix(int size);
void	transpose(double *m, int size);
// double	*submatrix(double *m, int size, int row, int col);
// double	det2x2(double *m);
// double	cofactor(double *m, int size, int i, int j);
// double	determinant(double *m, int size);
double	*invert(double *m, int size);
int		m2a(int size_j, int i, int j);
double	*mat_mat_prod(double *m1, double *m2, int size);
double  *mat_vec_prod(double *m, double *v);
double	**ray(double *origin, double *direction);
double	*position(double **ray, double t);
// void	intersect_sphere(double **ray, t_object *obj, t_intersect **lst);
// void	intersect_cylinder(double **ray, t_object *obj, t_intersect **lst);
// void	intersect_plane(double **ray, t_object *obj, t_intersect **lst);
t_intersect	*intersect_world(t_world *w, double **ray);
double	abs_f(double val);
t_intersect	*find_hit(t_intersect *lst);
void		free_ray(double **ray);
double	*translate(double x, double y, double z);
double	*scale(double f);
double	*rot_x(double phi);
double	*rot_y(double phi);
double	*rot_z(double phi);
double	**transform(double **ray, double *m);

#endif
