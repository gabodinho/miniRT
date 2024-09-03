/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/03 21:10:20 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_intersect(t_intersect *list)
{
	int	i;

	i = 0;
	while (list)
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

void	print_world_info(t_world *w)
{
	t_object *obj;

	for (int i = 0; i < w -> n_obj; i++)
	{
		obj = w -> objects[i];
		printf("shape: %d\n\npoint: ", obj ->shape);
		print_vec(obj->obj_p, 0);
		printf("normal: ");
		if (obj->shape == CYLNDR || obj->shape == PLANE)
			print_vec(obj->norm_v, 0);
		printf("colour: ");
		print_vec(obj ->colour, -1);
		if (obj->shape == CYLNDR || obj->shape == SPHERE)
			printf("diam: %f\n", obj -> diam);
		if (obj->shape == CYLNDR)
			printf("height: %f\n", obj ->height);
	}
	printf("camera:\n\nnormal: ");
	print_vec(w->cam->norm_v, 0);
	printf("view point: ");
	print_vec(w->cam->view_p, 0);
	printf("light:\n\npoint: ");
	print_vec(w->light_p, 0);
	printf("bright: %f\namb colour: ", w->light_bright);
	print_vec(w->amb_colour, -1);
}

static void	escape(void *ptr)
{
	mlx_t	*mlx;

	mlx = (mlx_t *) ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static void	free_cam(t_camera *cam)
{
	free(cam -> view_p);
	free(cam -> norm_v);
	free(cam -> transform);
	free(cam -> inv_trans);
	free(cam);
}

static void	free_object(t_object *obj)
{
	free(obj -> obj_p);
	free(obj -> norm_v);
	free(obj -> transform);
	free(obj -> inv_trans);
	free(obj -> colour);
	free(obj);
}

void	clean_up(t_world *w)
{
	int	i;

	i = -1;
	while (++i < w -> n_obj)
	{
		if (w -> objects[i])
			free_object(w -> objects[i]);
	}
	free(w -> objects);
	free(w -> light_p);
	free(w -> amb_colour);
	if (w -> cam)
		free_cam(w -> cam);
	free(w);
}

int	main(int argc, char *argv[])
{
	t_world	*w;
	mlx_t			*mlx;
	mlx_image_t		*image;

	// char *a = "1234.356,1234.356";
	// char *b = "1234356,12r34.356,-1234.356";
	// char *c = "-123,1,0";
	// char *d = "1234356.,1234.356,1234.356";
	// char *e = "1234356,1234.356 ,1234.356";
	// char *f = "123,1234.356,,345";
	// char *g = "1234,252435,22354,";
	// printf("%s\n", a);
	// printf("%d; after: ", check_touple(&a));
	// printf("%s\n", a);
	// printf("%s\n", b);
	// printf("%d; after: ", check_touple(&b));
	// printf("%s\n", b);
	// printf("%s\n", c);
	// printf("%d; after: ", check_touple(&c));
	// printf("%s\n", c);
	// printf("%s\n", d);
	// printf("%d; after: ", check_touple(&d));
	// printf("%s\n", d);
	// printf("%s\n", e);
	// printf("%d; after: ", check_touple(&e));
	// printf("%s\n", e);
	// printf("%s\n", f);
	// printf("%d; after: ", check_touple(&f));
	// printf("%s\n", f);
	// printf("%s\n", g);
	// printf("%d; after: ", check_touple(&g));
	// printf("%s\n", g);
	// // printf("%d, %s; new pos: %s\n", a, check_number(&a), a);
	
	// printf("input check: %d\n", check_sphere("	0.0,0.0,10  10,234,234 10,0,255"));
	
	
	if (argc != 2)
		return (1);
	if (validate_input_file(argv[1]))
		return (2);
	else
		printf("file name: valid!\n");
	if (syntax_check(argv[1]))
		return (3);
	else
		printf("syntax check: pass!\n");
	w = init_world(argv[1]);
	mlx = mlx_init(HSIZE, VSIZE, "MLX42", true);
	image = mlx_new_image(mlx, HSIZE, VSIZE);
	print_world_info(w);
	render(w, w -> cam, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, escape, (void *) mlx);
	mlx_loop(mlx);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	clean_up(w);
	return (0);
}
