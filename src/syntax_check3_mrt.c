/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check3_mrt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:44:37 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 20:16:13 by ggiertzu         ###   ########.fr       */
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
		type = "semantics check: failed: too many light sources\n";
	else if (ret_val == 5)
		type = "semantics check: failed: too many ambient light sources\n";
	else if (ret_val == 6)
		type = "semantics check: failed: too many cameras\n";
	else if (ret_val == 7)
		type = "input: invalid\n";
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
