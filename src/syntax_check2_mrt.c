/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2_mrt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 20:08:05 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 20:12:53 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return (4);
	if (check_touple(&line))
		return (2);
	line = line + skip_empty(line);
	if (check_number(&line))
		return (2);
	return (0);
}
