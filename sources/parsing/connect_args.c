/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:22:07 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 15:53:13 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_connected(t_dlist *lst)
{
	t_split_cmd	*data;
	t_split_cmd	*next;

	while (lst)
	{
		data = lst->data;
		if (lst->next)
			next = lst->next->data;
		if (data->connected && lst->next && next->type > double_quotes)
			data->connected = 0;
		lst = lst->next;
	}
}

int	parse_cmd_var(t_dlist *lst)
{
	t_split_cmd	*data;

	while (lst)
	{
		data = lst->data;
		if (data->type == no_quote || data->type == double_quotes)
			pre_expand(data, lst);
		else
			ft_dl_add_back(&get_cmds()->split_var,
				ft_dl_new(dup_split_cmd(data)));
		lst = lst->next;
	}
	return (SUCCESS);
}

void	add_pre_ex(t_dlist **lst, t_split_cmd **data, t_split_cmd **new)
{
	while (*lst && (*data)->connected)
	{
		*lst = (*lst)->next;
		if (*lst)
		{
			*data = (*lst)->data;
			ft_dl_add_back(&(*new)->pre_expand,
				ft_dl_new(dup_split_cmd(*data)));
		}
	}
}

void	connect_args(t_dlist *lst)
{
	t_split_cmd	*data;
	t_split_cmd	*new;

	while (lst)
	{
		data = lst->data;
		if (data->type <= double_quotes)
		{
			new = create_split_cmd(ft_strdup(""), pre_exp);
			ft_dl_add_back(&new->pre_expand, ft_dl_new(dup_split_cmd(data)));
			add_pre_ex(&lst, &data, &new);
			ft_dl_add_back(&get_cmds()->connected, ft_dl_new(new));
		}
		else
			ft_dl_add_back(&get_cmds()->connected,
				ft_dl_new(dup_split_cmd(data)));
		if (lst)
			lst = lst->next;
	}
}
