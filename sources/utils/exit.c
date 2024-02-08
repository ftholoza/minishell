/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 03:02:40 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/02 17:27:29 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_hd(t_split_cmd *command)
{
	if (command->type == here_doc || command->type == here_doc_quote)
	{
		if (command->str)
		{
			unlink(command->str);
			free(command->str);
			command->str = NULL;
		}
	}
}

void	unlink_all(t_exec_cmd *subs)
{
	t_dlist		*lst;
	t_exec_cmd	*child;
	t_dlist		*redir;
	t_split_cmd	*command;

	if (!subs)
		return ;
	lst = subs->cmds;
	while (lst)
	{
		child = lst->data;
		if (child->type != cmd)
			unlink_all(child);
		else if (child->cmd)
		{
			redir = child->cmd->redir;
			while (redir)
			{
				command = redir->data;
				unlink_hd(command);
				redir = redir->next;
			}
		}
		lst = lst->next;
	}
}

void	free_env(void *data)
{
	t_env	*env;

	env = data;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}

void	close_all_fds(void)
{
	int	i;

	i = 2;
	while (++i < 1024)
		close(i);
}

void	full_exit(int return_value)
{
	t_ms	*ms;

	ms = get_ms();
	ft_dl_clear(&ms->env, &free_env);
	ft_free(0, "v", ms->curr_dir);
	clear_cmds_lst();
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exit (return_value);
}
