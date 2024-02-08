/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:25:14 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/20 01:00:54 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_init_var(int low, int high, t_dlist **pivot, t_dlist **low_list)
{
	int		i;

	i = -1;
	while (++i < high)
	{
		if (i == low)
			*low_list = *pivot;
		*pivot = (*pivot)->next;
	}
}

int	dl_partition(t_dlist *list, int low, int high, int (*cmp)(void *, void *))
{
	t_dlist	*pivot;
	t_dlist	*low_list;
	t_dlist	*current_list;
	int		i;

	pivot = list;
	set_init_var(low, high, &pivot, &low_list);
	i = low - 1;
	current_list = low_list;
	while (++i < high)
	{
		if ((*cmp)(current_list->data, pivot->data))
		{
			ft_dl_swap(low_list, current_list);
			low_list = low_list->next;
			low++;
		}
		current_list = current_list->next;
	}
	ft_dl_swap(low_list, pivot);
	return (low);
}

void	dl_quicksrt(t_dlist *lst, int low, int high, int (*cmp)(void *, void *))
{
	int	pivot;

	if (low < high)
	{
		pivot = dl_partition(lst, low, high, cmp);
		dl_quicksrt(lst, low, pivot - 1, cmp);
		dl_quicksrt(lst, pivot + 1, high, cmp);
	}
}

void	ft_dl_sort(t_dlist *list, int (*sort_cmp)(void *, void *))
{
	dl_quicksrt(list, 0, ft_dl_size(list) - 1, sort_cmp);
}
