/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2_mrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:23:27 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/25 18:17:27 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_lst(t_intersect *lst)
{
	int	res;

	res = 0;
	while (lst)
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

void	append_intersect(t_intersect **lst, double *xs, t_object *obj)
{
	t_intersect	*new1;
	t_intersect	*new2;
	t_intersect	*ptr;

	new1 = malloc(sizeof(t_intersect));
	new1 -> obj = obj;
	new1 -> t = xs[0];
	new1 -> next = NULL;
	if (obj -> shape != PLANE)
	{
		new2 = malloc(sizeof(t_intersect));
		new2 -> obj = obj;
		new2 -> t = xs[1];
		new1 -> next = new2;
		new2 -> next = NULL;
	}
	if (!*lst)
	{
		*lst = new1;
		return ;
	}
	ptr = *lst;
	while (ptr -> next)
		ptr = ptr -> next;
	ptr -> next = new1;
}
