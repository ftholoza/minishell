/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:23:08 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 11:46:18 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_cmd(void *data)
{
	t_split_cmd	*split;

	split = data;
	if (split->str)
		free(split->str);
	ft_dl_clear(&split->pre_expand, &free_split_cmd);
	free(split);
}

void	free_computed_cmd(void *data)
{
	t_computed_cmd	*comp;
	int				i;

	comp = data;
	i = -1;
	if (comp->argv)
	{
		while (comp->argv[++i])
			free (comp->argv[i]);
		free (comp->argv);
	}
	ft_dl_clear(&comp->redir, &free_split_cmd);
	i = -1;
	if (comp->pre_expand)
	{
		while (comp->pre_expand[++i])
			ft_dl_clear(&comp->pre_expand[i], &free_split_cmd);
		free (comp->pre_expand[i]);
	}
	if (comp->pre_expand)
		free (comp->pre_expand);
	free(comp);
}

void	free_exec_cmd(void *data)
{
	t_exec_cmd	*exec;

	exec = data;
	if (exec->cmd)
		free_computed_cmd(exec->cmd);
	ft_dl_clear(&exec->cmds, &free_exec_cmd);
	ft_dl_clear(&exec->redir, &free_split_cmd);
	free(exec);
	exec = NULL;
}

void	clear_cmds_lst(void)
{
	t_cmds			*cmds;

	cmds = get_cmds();
	ft_dl_clear(&cmds->split_quote, &free_split_cmd);
	ft_dl_clear(&cmds->split_space, &free_split_cmd);
	ft_dl_clear(&cmds->split_special, &free_split_cmd);
	ft_dl_clear(&cmds->split_var, &free_split_cmd);
	ft_dl_clear(&cmds->connected, &free_split_cmd);
	ft_dl_clear(&cmds->computed, &free_computed_cmd);
	if (cmds->subshell)
		free_exec_cmd(cmds->subshell);
	ft_bzero(cmds, sizeof(t_cmds));
}
