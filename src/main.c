/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 13:02:45 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_intersect(t_intersect *list)
{
	int	i;

	i = 0;
	while(list)
	{
		printf("obj %d: %d, with itersect val: %f\n", i++, list -> obj -> shape, list -> t);
		list = list -> next;
	}
}

void    print_vec(double *v, int size)
{
    char *str;

	if (!v)
		return;
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
            printf("row %d: %f %f %f %f\n", i, v[i*size], v[size*i+1], v[size*i+2], v[size*i+3]);
        return;
    }
	else if (size == -1)
	{
		str = "c";
		printf("%s: %f, %f, %f\n", str, v[0], v[1], v[2]);
		return ;
	}
    if (v[3])
        str = "point";
    else
        str = "vector";
    printf("this is a %s: %f, %f, %f\n", str, v[0], v[1], v[2]);
}

/*
void    test_colour_at(t_world *w, t_camera *c)
{
	int		i;
	int		j;
	double	*colour;

	i = -1;
	while (++i < HSIZE)
	{
		j = -1;
		while (++j < VSIZE)
		{
			colour = color_at(w, ray_for_pixel(c, i, j));
			printf("x,y: %d,%d ", i, j);
			print_vec(colour, -1);
			free(colour);
		}
	}
}
*/

int	main(void)
{
	t_world *w2 = malloc(sizeof(t_world));
	w2 -> amb_colour = point(0.6, 0.6, 0.6);
	w2 -> light_bright = 0.9;
	w2 -> light_p = point(-5, 5, -10);
	w2 -> n_obj = 3;
	w2 -> objects = malloc(sizeof(t_object *) * w2 -> n_obj);
	char *str = "-5,-2,0 0.5773,0.5773,-0.5773 50,250,0";
	printf("%s\n", str);
	t_object *plane = init_plane(str);
	w2->objects[0] = plane;
	char *str2 = "0.0,0.0,10 10 10,0,255";
	printf("%s\n", str2);
	t_object *sphere = init_sphere(str2);
	w2->objects[1] = sphere;
	char *str3 = "0.0,0.0,10 1,0,0 2 20 255,0,100";
	printf("%s\n", str3);
	t_object *cyl = init_cylinder(str3);
	w2->objects[2] = cyl;
	printf("plane:\n");
	print_vec(plane -> norm_v, 0);
	print_vec(plane -> obj_p, 0);
	print_vec(plane -> colour, -1);
	printf("sphere:\n");
	printf("diam: %f\n", sphere -> diam);
	print_vec(sphere-> obj_p, 0);
	print_vec(sphere-> colour, -1);
	printf("cylinder:\n");
	printf("diam: %f\n", cyl -> diam);
	printf("height: %f\n", cyl -> height);
	print_vec(cyl-> obj_p, 0);
	print_vec(cyl -> norm_v, 0);
	print_vec(cyl-> colour, -1);
	// t_camera *cam;
    // cam = malloc(sizeof(t_camera));
	// cam -> nv = vector(0, 0, 1);
	// cam -> vp = point(0, 0, -5);
    // cam -> field_of_view = 90;
    // init_camera(cam);
	// test_colour_at(w2, cam);
	char *str4 = "0.0,0,-5 0,0,1 90";
	t_camera *cam2 = init_camera(str4);

	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx = mlx_init(HSIZE, VSIZE, "MLX42", true);
	image = mlx_new_image(mlx, HSIZE, VSIZE);
	render(w2, cam2, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
    return (0);
}
/*
int main(void)
{
	t_world *w2 = malloc(sizeof(t_world));
	t_object *obj4 = malloc(sizeof(t_object));
	obj4 -> shape = SPHERE;
	obj4 -> transform = translate(-1, 0.5, 0);
	obj4 -> inv_trans = invert(obj4 -> transform, 4);
	obj4 -> colour = point(0.5, 0, 0);
	t_object *obj2 = malloc(sizeof(t_object));
	obj2 -> shape = PLANE;
	// keep in mind the order of the transformations!!
	double *m = rot_x(M_PI / 2);
	double *m2 = translate(0, 0, 2.99);
	obj2 -> transform = mat_mat_prod(m2, m, 4);
	// print_vec(obj2 -> transform, 4);
	obj2 -> inv_trans = invert(obj2 -> transform, 4);
	// print_vec(obj2 -> inv_trans, 4);
	// print_vec(mat_mat_prod(obj2 -> transform, obj2 -> inv_trans, 4), 4);
	obj2 -> colour = point(0.5, 0.5, 0.5);
	t_object *obj1 = malloc(sizeof(t_object));
	obj1 -> shape = PLANE;
	obj1 -> transform = translate(0, -0.5, 0);
	obj1 -> inv_trans = invert(obj1 -> transform, 4);
	obj1 -> colour = point(0, 0.5, 1);
	t_object *obj3 = malloc(sizeof(t_object));
	obj3 -> shape = CYLNDR;
	obj3 -> transform = rot_x(M_PI / 6);
	obj3 -> transform = scale(1, -2, 1);
	obj3 -> inv_trans = invert(obj3 -> transform, 4);
	obj3 -> colour = point(0, 1, 1);
	w2 -> amb_colour = point(0.6, 0.6, 0.6);
	w2 -> light_bright = 0.9;
	w2 -> light_point = point(-5, 5, -10);
	w2 -> n_obj = 4;
	w2 -> objects = malloc(sizeof(t_object *) * w2 -> n_obj);
	w2->objects[0] = obj4;
	w2->objects[1] = obj2;
	w2->objects[2] = obj1;
	w2->objects[3] = obj3;
	t_camera *cam;
    cam = malloc(sizeof(t_camera));
    cam -> vp_x = 0;
    cam -> vp_y = 0;
    cam -> vp_z = -3;
    cam -> nv_x = 0;
    cam -> nv_y = 0;
    cam -> nv_z = 1;
    cam -> field_of_view = 90;
    init_camera(cam);
	// test_colour_at(w2, cam);

	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx = mlx_init(HSIZE, VSIZE, "MLX42", true);
	image = mlx_new_image(mlx, HSIZE, VSIZE);
	render(w2, cam, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
    return (0);
}
 */
