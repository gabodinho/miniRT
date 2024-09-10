/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:16:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/10 19:23:20 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "ft_printf.h"
# include "structs_minirt.h"
# include <MLX42/MLX42.h>

double		*vector(double a, double b, double c);
double		*point(double a, double b, double c);
void		normalize(double tuple[4]);
double		dot_product(double *v1, double *v2);
double		*cross_product(double *v1, double *v2);
double		*identity_matrix(int size);
void		transpose(double *m, int size);
double		*invert(double *m, int size);
int			m2a(int size_j, int i, int j);
double		*mat_mat_prod(double *m1, double *m2);
double		*mat_vec_prod(double *m, double *v);
double		**ray(double *origin, double *direction);
double		*position(double **ray, double t);
t_intersect	*intersect_world(t_world *w, double **ray);
double		abs_f(double val);
t_intersect	*find_hit(t_intersect *lst);
void		free_ray(double **ray);
double		*translate(double x, double y, double z);
double		*scale(double x, double y, double z);
double		**transform(double **ray, double *m);
double		*substract_points(double *a, double *b);
double		**ray_for_pixel(t_camera *cam, int x, int y);
double		*reflect(double *in, double *normal);
void		hadamard_prod(double *c1, double *c2);
void		vec_skal_prod(double *v, double s, int size);
double		*copy_vec(double *v, int size);
double		*lighting(t_world *w, t_comps *comps);
void		free_comps(t_comps *comps);
void		free_intersect(t_intersect *xs);
void		render(t_world *w, t_camera *c, mlx_image_t *img);
int			count_lst(t_intersect *lst);
int			is_shadowed(t_world *w, double *p);
t_object	*init_plane(char *input);
double		*get_double_touple(char **str, int kind);
int			get_double(double *f, char *str);
t_object	*init_sphere(char *input);
t_object	*init_cylinder(char *input);
t_camera	*init_camera(char *input);
t_world		*init_world(char *file);
int			skip_empty(char *line);
void		intersect_cylinder(double **ray, t_object *obj, t_intersect **lst);
void		append_intersect(t_intersect **lst, double *xs, t_object *obj);
void		clean_up(t_world *w);
t_object	*create_empty_obj(void);
t_world		*create_empty_world(void);
void		abort_prog(char *str, t_world *w);
int			check_number(char **ptr);
int			check_touple(char **ptr);
int			check_sphere(char *get_line);
int			syntax_check(char *file);
int			semantic_check(t_world *w);
int			print_error(int ret_val, char *msg);
int			check_sphere(char *line);
int			check_cylinder(char *line);
int			check_plane(char *line);
int			check_light(char *line);
double		*get_rot_mat(double *nv);

// to be deleted
void		print_vec(double *v, int size);
double		*normal_at(t_object *obj, double *p_w);

#endif
