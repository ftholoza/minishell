/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:22:24 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/13 16:25:12 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dl_new(void *data)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
