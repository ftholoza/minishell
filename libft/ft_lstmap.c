/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:48:57 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:28:37 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*beginlst;
	t_list	*newlst;

	if (!f || !del)
		return (NULL);
	beginlst = NULL;
	while (lst)
	{
		newlst = ft_lstnew((*f)(lst->content));
		if (!newlst)
		{
			ft_lstclear(&beginlst, del);
			return (NULL);
		}
		ft_lstadd_back(&beginlst, newlst);
		lst = lst->next;
	}
	return (beginlst);
}
