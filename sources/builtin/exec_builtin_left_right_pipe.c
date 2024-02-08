/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_left_right_pipe.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:11:35 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 13:31:29 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_left_right_pipe_b(t_exec_cmd *cmd, int (*builtin)(t_exec_cmd *))
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			full_exit(FAILURE);
	close_fd(&cmd->pipe_fd[0]);
	dup2(cmd->in_fd, 0);
	dup2(cmd->out_fd, 1);
	close_fd(&cmd->pipe_fd[1]);
	full_exit(builtin(cmd));
}

int	exec_left_right_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
		int (*builtin)(t_exec_cmd *))
{
	pid_t	pid;

	signal(SIGINT, &update_signal);
	if (pipe(cmd->pipe_fd) < 0)
		return (err(NULL, "unable to create pipe", ERR_PIPE));
	cmd->in_fd = ((t_exec_cmd *)lst->prev->data)->pipe_fd[0];
	cmd->out_fd = cmd->pipe_fd[1];
	pid = fork();
	if (pid < 0)
		return (close_fds_err(lst));
	if (!pid)
		exec_left_right_pipe_b(cmd, builtin);
	add_pid(pid);
	close_fd(&cmd->pipe_fd[1]);
	return (SUCCESS);
}
