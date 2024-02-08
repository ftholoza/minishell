/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:23:57 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/20 00:38:06 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_swap(t_dlist *a, t_dlist *b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}
