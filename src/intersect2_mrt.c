/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2_mrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:23:27 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/21 20:50:09 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_lst(t_intersect *lst)
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


