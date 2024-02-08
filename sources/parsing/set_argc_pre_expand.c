/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argc_pre_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:15:45 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:03:21 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd_argc(t_dlist *lst, t_computed_cmd *cmd)
{
	t_split_cmd	*data;

	cmd->argc = 0;
	while (lst)
	{
		data = lst->data;
		if (data->type == pre_exp)
			(cmd->argc)++;
		else if (data->type < piping)
			lst = lst->next;
		else
			break ;
		if (lst)
			lst = lst->next;
	}
}

void	save_pre_argv(t_computed_cmd *cmd, t_split_cmd *data, int *i)
{
	cmd->pre_expand[*i] = data->pre_expand;
	data->pre_expand = NULL;
	(*i)++;
}

t_dlist	*set_cmd_pre_expand(t_dlist *lst, t_computed_cmd *cmd)
{
	t_split_cmd	*data;
	int			i;

	i = 0;
	while (lst)
	{
		data = lst->data;
		if (data->type == pre_exp)
			save_pre_argv(cmd, data, &i);
		else if (data->type < piping)
		{
			set_cmd_redir(lst, cmd);
			lst = lst->next;
		}
		else
			break ;
		if (lst)
			lst = lst->next;
	}
	cmd->argv[i] = NULL;
	cmd->pre_expand[i] = NULL;
	return (lst);
}
