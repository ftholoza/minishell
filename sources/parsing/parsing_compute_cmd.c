/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_compute_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:29:32 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 21:54:00 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_hd(t_split_cmd *hd_end)
{
	t_dlist		*lst;
	t_split_cmd	*pre_ex;

	lst = hd_end->pre_expand;
	hd_end->type = no_quote;
	while (lst)
	{
		pre_ex = lst->data;
		hd_end->str = ft_str_append(hd_end->str, pre_ex->str);
		if (hd_end->type == no_quote)
			hd_end->type = pre_ex->type;
		lst = lst->next;
	}
}

void	set_cmd_redir(t_dlist *lst, t_computed_cmd *cmd)
{
	t_split_cmd	*data;

	data = lst->data;
	if (data->type == input_redirect)
		ft_dl_add_back(&cmd->redir,
			ft_dl_new(dup_redir_cmd(lst->next->data, input_redirect)));
	else if (data->type == here_doc)
	{
		connect_hd(lst->next->data);
		if (((t_split_cmd *)lst->next->data)->type != no_quote)
			data->type = here_doc_quote;
		heredoc(lst->next->data);
		ft_dl_add_back(&cmd->redir,
			ft_dl_new(dup_redir_cmd(lst->next->data, data->type)));
	}
	else if (data->type == output_redirect)
		ft_dl_add_back(&cmd->redir,
			ft_dl_new(dup_redir_cmd(lst->next->data, output_redirect)));
	else if (data->type == append_redirect)
		ft_dl_add_back(&cmd->redir,
			ft_dl_new(dup_redir_cmd(lst->next->data, append_redirect)));
}

t_dlist	*get_cmd(t_dlist *lst)
{
	t_computed_cmd	*new;
	t_cmds			*cmds;

	cmds = get_cmds();
	new = create_comp_cmd(cmd);
	if (!new)
		return (err_null("minishell: malloc error"));
	set_cmd_argc(lst, new);
	new->argv = malloc(sizeof(char *) * (new->argc + 1));
	if (!new->argv)
		return (err_null("minishell: malloc error"));
	ft_bzero(new->argv, sizeof(char *) * (new->argc) + 1);
	new->pre_expand = malloc(sizeof(t_dlist *) * (new->argc + 1));
	if (!new->pre_expand)
		return (err_null("minishell: malloc error"));
	lst = set_cmd_pre_expand(lst, new);
	ft_dl_add_back(&cmds->computed, ft_dl_new(new));
	return (lst);
}

int	compute_cmds(void)
{
	t_dlist		*lst;
	t_split_cmd	*data;

	lst = get_cmds()->connected;
	while (lst)
	{
		data = lst->data;
		if (data->type < piping)
			lst = get_cmd(lst);
		if (lst && ((t_split_cmd *)(lst->data))->type >= piping)
		{
			ft_dl_add_back(&get_cmds()->computed,
				ft_dl_new(create_comp_cmd(((t_split_cmd *)(lst->data))->type)));
		}
		if (lst)
			lst = lst->next;
	}
	if (get_ms()->last_exit == 131)
	{
		get_ms()->last_exit = 130;
		return (FAILURE);
	}
	return (SUCCESS);
}
