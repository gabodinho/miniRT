/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2_mrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:23:27 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/16 01:29:09 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	count_lst(t_intersect *lst)
{
	int	res;

	res = 0;
	while(lst)
	{
		res++;
		lst = lst -> next;
	}
	return (res);
}

// hit is the smallest non-negative intersection value
t_intersect	*find_hit(t_intersect *lst)
{
	int			i;
	t_intersect	*temp;
	int			len;

	i = 0;
	len = count_lst(lst);
	while (lst && lst -> t < 0)
	{
		lst = lst -> next;
		i++;
	}
	temp = lst;
	while (i < len)
	{
		if (lst -> next && lst -> next -> t < temp -> t
			&& lst -> next -> t >= 0)
			temp = lst -> next;
		lst = lst -> next;
		i++;
	}
	return (temp);
}

double	**transform(double **ray, double *m)
{
	double	**ray_obj;

	ray_obj = malloc(sizeof(double *) * 2);
	ray_obj[0] = mat_vec_prod(m, ray[0]);
	ray_obj[1] = mat_vec_prod(m, ray[1]);
	return (ray_obj);
}

// void	sort_intersections(t_intersect **lst)
// {
// 	int			i;
// 	int			j;
// 	int			len;
// 	t_intersect	*ptr;
// 	double		temp;

// 	if (!*lst)
// 		return ;
// 	i = 0;
// 	ptr = *lst;
// 	len = count_lst(*lst);
// 	temp = (*lst) -> t;
// 	while (i++ < len)
// 	{
// 		j = 0;
// 		while (j++ < len - i)
// 		if (ptr -> next && temp > ptr -> next -> t)
// 			temp = ptr -> next -> t;
// 		ptr = ptr -> next;

// 	}
// }
