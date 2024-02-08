/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_left_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:14:38 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/03 08:24:28 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_left_pipe_b(t_exec_cmd *cmd, int (*builtin)(t_exec_cmd *))
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			full_exit(FAILURE);
	dup2(cmd->in_fd, 0);
	dup2(cmd->parent->out_fd, 1);
	full_exit(builtin(cmd));
}

int	exec_left_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
		int (*builtin)(t_exec_cmd*))
{
	pid_t	pid;

	signal(SIGINT, &update_signal);
	cmd->in_fd = ((t_exec_cmd *)lst->prev->data)->pipe_fd[0];
	cmd->out_fd = cmd->parent->out_fd;
	pid = fork();
	if (pid < 0)
		return (close_fds_err(lst));
	get_ms()->last_pipe_pid = pid;
	if (!pid)
		exec_left_pipe_b(cmd, builtin);
	else
	{
		add_pid(pid);
		wait_childs(cmd);
		close_fds(lst);
	}
	return (SUCCESS);
}
