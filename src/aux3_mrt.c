/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:44:38 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/04 12:51:08 by gabodinho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

int	skip_empty(char *line)
{
	int	i;

	i = 0;
	while (ft_strchr("\t ", line[i]))
		i++;
	return (i);
}

int	get_double(double *f, char *str)
{
	int		i;
	int		len_dec;
	double	temp;

	i = 0;
	len_dec = 0;
	*f = (double) ft_atoi(str);
	while (!ft_strchr(", .\n", str[i]))
		i++;
	if (str[i] == ',')
		return (i + 1);
	else if (str[i] == '\n' || str[i] == ' ')
		return (i);
	else
		i++;
	temp = (double)(ft_atoi(str + i));
	while (!ft_strchr(", \n", str[i + len_dec]))
		len_dec++;
	*f += temp / pow(10, len_dec);
	if (*f < 1 && *f > 0 && *str == '-')
		*f *= -1;
	if (str[i + len_dec] == ',')
		return (i + len_dec + 1);
	else
		return (i + len_dec);
}

double	*get_double_touple(char **str, int kind)
{
	double	temp[3];
	int		i;

	i = -1;
	while (++i < 3)
		*str += get_double(temp + i, *str);
	while (**str == ' ')
		*str += 1;
	if (kind == 0)
		return (point(temp[0], temp[1], temp[2]));
	else if (kind == 1)
		return (vector(temp[0], temp[1], temp[2]));
	else
		return (point(temp[0] / 255.0, temp[1] / 255.0, temp[2] / 255.0));
}

void	abort_prog(char *str, t_world *w)
{
	perror(str);
	clean_up(w);
	exit(1);
}

t_world	*create_empty_world(void)
{
	t_world	*w;

	w = malloc(sizeof(t_world));
	if (!w)
	{
		perror("create_empty_world");
		exit(1);
	}
	w -> amb_colour = NULL;
	w -> light_p = NULL;
	w -> light_bright = 0;
	w -> objects = NULL;
	w -> cam = NULL;
	w -> n_obj = 0;
	return (w);
}
