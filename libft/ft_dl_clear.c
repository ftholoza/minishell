/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:33:29 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/13 16:17:14 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_clear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*next;

	if (lst)
	{
		while (*lst)
		{
			next = (*lst)->next;
			ft_dl_del(*lst, del);
			*lst = next;
		}
	}
}
