/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/22 00:41:09 by ggiertzu         ###   ########.fr       */
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

int main(void)
{
	t_world *w2 = malloc(sizeof(t_world));
	// t_object *obj4 = malloc(sizeof(t_object));
	// obj4 -> shape = SPHERE;
	// obj4 -> transform = translate(-1, 0.5, 0);
	// obj4 -> inv_trans = invert(obj4 -> transform, 4);
	// obj4 -> colour = point(0.5, 0, 0);
	// t_object *obj2 = malloc(sizeof(t_object));
	// obj2 -> shape = PLANE;
	// // keep in mind the order of the transformations!!
	// double *m = rot_x(M_PI / 2);
	// double *m2 = translate(0, 0, 2.99);
	// obj2 -> transform = mat_mat_prod(m2, m, 4);
	// // print_vec(obj2 -> transform, 4);
	// obj2 -> inv_trans = invert(obj2 -> transform, 4);
	// // print_vec(obj2 -> inv_trans, 4);
	// // print_vec(mat_mat_prod(obj2 -> transform, obj2 -> inv_trans, 4), 4);
	// obj2 -> colour = point(0.5, 0.5, 0.5);
	// t_object *obj1 = malloc(sizeof(t_object));
	// obj1 -> shape = PLANE;
	// obj1 -> transform = translate(0, -0.5, 0);
	// obj1 -> inv_trans = invert(obj1 -> transform, 4);
	// obj1 -> colour = point(0, 0.5, 1);
	t_object *obj3 = malloc(sizeof(t_object));
	obj3 -> shape = CYLNDR;
	obj3 -> transform = rot_x(M_PI * 2);
	obj3 -> inv_trans = invert(obj3 -> transform, 4);
	obj3 -> colour = point(0, 1, 1);
	w2 -> amb_colour = point(0.6, 0.6, 0.6);
	w2 -> light_bright = 0.9;
	w2 -> light_point = point(-5, 5, -10);
	w2 -> n_obj = 1;
	w2 -> objects = malloc(sizeof(t_object *) * w2 -> n_obj);
	// w2->objects[0] = obj4;
	// w2->objects[1] = obj2;
	// w2->objects[2] = obj1;
	w2->objects[0] = obj3;
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
