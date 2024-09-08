/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 22:11:36 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
void	print_intersect(t_intersect *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("obj %d: %d, with itersect val: %f\n",
			i++, list -> obj -> shape, list -> t);
		list = list -> next;
	}
}
*/

void	print_vec(double *v, int size)
{
	char	*str ;

	if (!v)
		return ;
	if (size > 0)
	{
		int i = 0;
		while (i < size)
		i++,
        	printf("row %d: %f %f %f %f\n", i, v[i*size],
				v[size*i+1], v[size*i+2], v[size*i+3]);
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
*/
static int	validate_input_file(char *filename)
{
	int		fd;
	size_t	len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strncmp(filename + len - 3, ".rt", 3) != 0)
		return (print_error(1, "Expected .rt file\n"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (2);
	}
	close(fd);
	return (0);
}

static void	escape(void *ptr)
{
	mlx_t	*mlx;

	mlx = (mlx_t *) ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static t_world	*run_checks(int argc, char *argv[])
{
	t_world	*w;

	if (argc != 2)
	{
		print_error(7, "too many parameters\n");
		exit(1);
	}
	if (validate_input_file(argv[1]))
		exit(2);
	else
		printf("file name: valid!\n");
	if (syntax_check(argv[1]))
		exit(3);
	else
		printf("syntax check: pass!\n");
	w = init_world(argv[1]);
	if (semantic_check(w))
		exit(4);
	else
		printf("semantics check: pass!\n");
	return (w);
}

int	main(int argc, char *argv[])
{
	t_world			*w;
	mlx_t			*mlx;
	mlx_image_t		*image;

	w = run_checks(argc, argv);
	mlx = mlx_init(HSIZE, VSIZE, "MLX42", true);
	image = mlx_new_image(mlx, HSIZE, VSIZE);
	render(w, w -> cam, image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, escape, (void *) mlx);
	mlx_loop(mlx);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	clean_up(w);
	return (0);
}
