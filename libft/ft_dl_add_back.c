/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:57:10 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/13 16:11:02 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_add_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (!new)
		return ;
	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = ft_dl_last(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}
