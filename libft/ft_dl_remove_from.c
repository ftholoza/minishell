/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_remove_from.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:44:29 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/21 08:44:07 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dl_remove_from(t_dlist **lst, t_dlist *elem, void (*del)(void *))
{
	t_dlist	*next;

	next = NULL;
	if (!lst || !elem || !del)
		return (NULL);
	if (elem->prev && elem->next)
	{
		next = elem->next;
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	else if (elem->prev)
		elem->prev->next = NULL;
	else
	{
		next = elem->next;
		if (next)
			elem->next->prev = NULL;
		*lst = next;
	}
	(*del)(elem->data);
	free(elem);
	elem = NULL;
	return (next);
}
