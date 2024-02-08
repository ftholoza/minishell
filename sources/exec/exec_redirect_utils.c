/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:28:36 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:28:47 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_redir(int *quote, t_dlist *lst, t_split_cmd *data)
{
	t_split_cmd	*pre_ex;

	*quote = 0;
	while (lst)
	{
		pre_ex = lst->data;
		if (pre_ex->type != no_quote && ft_strchr(pre_ex->str, '*') != NULL)
			*quote = 1;
		ft_expander(pre_ex);
		data->str = ft_str_append(data->str, pre_ex->str);
		lst = lst->next;
	}
}

t_dlist	*wildcard_redir(t_split_cmd *data, int *quote)
{
	t_wildcard	*w;
	t_dlist		*lst;
	t_dlist		*wild_redir;

	wild_redir = NULL;
	w = wildcard(data->str);
	lst = w->files;
	if (lst && !(*quote) && ft_strchr(data->str, '*'))
	{
		while (lst)
		{
			ft_dl_add_back(&wild_redir,
				ft_dl_new(create_split_cmd(ft_strdup(lst->data), data->type)));
			lst = lst->next;
		}
		ft_dl_clear(&w->files, &free);
	}
	else
		ft_dl_add_back(&wild_redir,
			ft_dl_new(create_split_cmd(ft_strdup(data->str), data->type)));
	free(w);
	return (wild_redir);
}

int	next_in(t_dlist *lst)
{
	t_split_cmd	*data;

	while (lst)
	{
		data = lst->data;
		if (data->type <= here_doc_quote)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	next_out(t_dlist *lst)
{
	t_split_cmd	*data;

	while (lst)
	{
		data = lst->data;
		if (data->type > here_doc_quote)
			return (1);
		lst = lst->next;
	}
	return (0);
}
