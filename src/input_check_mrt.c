/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_mrt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:44:37 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 19:02:59 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_error(int ret_val, char *msg)
{
	char	*type;

	type = NULL;
	printf("Error\n");
	if (ret_val == 1)
		type = "file name: invalid\n";
	else if (ret_val == 2)
		type = "syntax check: failed\n";
	else if (ret_val == 3)
		type = "semantics check: failed\n";
	else if (ret_val == 4)
		type = 	"semantics check: failed: too many light sources\n";
	else if (ret_val == 5)
		type = 	"semantics check: failed: too many ambient light sources\n";
	else if (ret_val == 6)
		type = 	"semantics check: failed: too many cameras\n";
	printf("%s%s", type, msg);
	return (ret_val);
}

int	check_number(char **ptr)
{
	if (**ptr == '-')
		*ptr += 1;
	if (!ft_isdigit(**ptr))
		return (1);
	while (**ptr && ft_isdigit(**ptr))
		*ptr += 1;
	if (**ptr == '.')
		*ptr += 1;
	else
		return (0);
	if (!ft_isdigit(**ptr))
		return (1);
	while (**ptr && ft_isdigit(**ptr))
		*ptr += 1;
	return (0);
}

int	check_touple(char **ptr)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (check_number(ptr))
			return (1);
		if (i < 2 && **ptr == ',')
			*ptr += 1;
		else if (i < 2 && **ptr != ',')
			return (1);
	}
	return (0);
}

int	check_sphere(char *line)
{
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	return (0);
}

int	check_plane(char *line)
{
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	return (0);
}

int	check_cylinder(char *line)
{
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_touple(&line))
		return (2);
	return (0);
}

int	check_light(char *line)
{
	static int	n;

	if (++n > 1)
	{
		printf("yes indeed too many light sources\n");
		return (4);
	}
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	return (0);
}

int	check_ambient(char *line)
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

int	check_camera(char *line)
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

int	check_line(char *line)
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
	else
		return (1);
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


