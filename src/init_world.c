/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:43:23 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 13:17:10 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_light(t_world *w, char *input)
{
	w -> light_p = get_double_touple(&input, 0);
	input += get_double(&w -> light_bright, input);
}

void	set_ambient(t_world *w, char *input)
{
	double	amb_ratio;

	input += get_double(&amb_ratio, input);
	while (*input == ' ')
		input++;
	w -> amb_colour = get_double_touple(&input, 2);
	vec_skal_prod(w -> amb_colour, amb_ratio, 3);
}
