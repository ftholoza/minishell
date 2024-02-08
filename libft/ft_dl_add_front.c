/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_add_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:35:49 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/19 18:17:31 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_add_front(t_dlist **lst, t_dlist *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		new->next = *lst;
		(*lst)->prev = new;
	}
	*lst = new;
}
