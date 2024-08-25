/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:43:23 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 18:19:24 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_light(t_world *w, char *input)
{
	input += 1 + skip_empty(input + 1);
	w -> light_p = get_double_touple(&input, 0);
	input += get_double(&w -> light_bright, input);
}

static void	set_ambient(t_world *w, char *input)
{
	double	amb_ratio;

	input += 1 + skip_empty(input + 1);
	input += get_double(&amb_ratio, input);
	while (*input == ' ')
		input++;
	w -> amb_colour = get_double_touple(&input, 2);
	vec_skal_prod(w -> amb_colour, amb_ratio, 3);
}

static int	get_n_obj(char *file)
{
	int		fd;
	char	*line;
	int		res;

	fd = open(file, O_RDONLY);
	// include open protection
	line = get_next_line(fd);
	res = 0;
	while (line)
	{
		if (!ft_strncmp(line + skip_empty(line), "pl", 2)
			|| !ft_strncmp(line + skip_empty(line), "cy", 2)
			|| !ft_strncmp(line + skip_empty(line), "sp", 2))
			res++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (res);
}

static void	parse_line(char *line, t_world *w)
{
	static int	i;

	if (!ft_strncmp(line, "pl", 2))
		w -> objects[i++] = init_plane(line);
	else if (!ft_strncmp(line, "cy", 2))
		w -> objects[i++] = init_cylinder(line);
	else if (!ft_strncmp(line, "sp", 2))
		w -> objects[i++] = init_sphere(line);
	else if (!ft_strncmp(line, "C", 1))
		w -> cam = init_camera(line);
	else if (!ft_strncmp(line, "A", 1))
		set_ambient(w, line);
	else if (!ft_strncmp(line, "L", 1))
		set_light(w, line);
}

t_world	*init_world(char *file)
{
	t_world	*w;
	int		fd;
	char	*line;

	w = malloc(sizeof(t_world));
	// include malloc protection
	w -> n_obj = get_n_obj(file);
	w -> objects = malloc(sizeof(t_object *) * w -> n_obj);
	// include malloc protection
	fd = open(file, O_RDONLY);
	// include open protection
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line + skip_empty(line), w);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (w);
}
