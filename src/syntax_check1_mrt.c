/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check1_mrt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:05:57 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 20:48:42 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_ambient(char *line)
{
	static int	n;

	if (++n > 1)
		return (5);
	if (check_number(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	return (0);
}

static int	check_camera(char *line)
{
	static int	n;

	if (++n > 1)
		return (6);
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	return (0);
}

static int	check_line(char *line)
{
	line = line + skip_empty(line);
	if (!ft_strncmp(line, "sp", 2))
		return (check_sphere(line + 2 + skip_empty(line + 2)));
	else if (!ft_strncmp(line, "pl", 2))
		return (check_plane(line + 2 + skip_empty(line + 2)));
	else if (!ft_strncmp(line, "cy", 2))
		return (check_cylinder(line + 2 + skip_empty(line + 2)));
	else if (!ft_strncmp(line, "L", 1))
		return (check_light(line + 1 + skip_empty(line + 1)));
	else if (!ft_strncmp(line, "A", 1))
		return (check_ambient(line + 1 + skip_empty(line + 1)));
	else if (!ft_strncmp(line, "C", 1))
		return (check_camera(line + 1 + skip_empty(line + 1)));
	else if (!ft_strncmp(line, "\n", 1))
		return (0);
	else if (!ft_strncmp(line, "#", 1))
		return (0);
	else
		return (2);
}

static void	finish_loop(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		close(fd);
	}
}

int	syntax_check(char *file)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		count++;
		if (check_line(line))
		{
			print_error(check_line(line), "error at line ");
			printf("%d: %s", count, line);
			finish_loop(line, fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
