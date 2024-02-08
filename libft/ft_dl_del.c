/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:06:05 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/13 16:21:59 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_del(t_dlist *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->prev && lst->next)
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	else if (lst->prev)
		lst->prev->next = NULL;
	else if (lst->next)
		lst->next->prev = NULL;
	(*del)(lst->data);
	free(lst);
	lst = NULL;
}
