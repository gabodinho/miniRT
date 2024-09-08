/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_mrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:47:24 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/09/08 19:47:35 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
