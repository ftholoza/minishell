/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_left_right_pipe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:13:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 11:58:57 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_left_right_pipe_cmd(t_exec_cmd *cmd)
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			return (ERR_FILE);
	close_fd(&cmd->pipe_fd[0]);
	dup2(cmd->in_fd, 0);
	dup2(cmd->out_fd, 1);
	close_fd(&cmd->pipe_fd[1]);
	exec_prog(cmd);
	return (SUCCESS);
}

void	exec_left_right_pipe_subs(t_exec_cmd *cmd)
{
	close_fd(&cmd->pipe_fd[0]);
	dup2(cmd->in_fd, 0);
	dup2(cmd->out_fd, 1);
	close_fd(&cmd->pipe_fd[1]);
	exec_shell(cmd);
	close_all_fds();
	full_exit(cmd->exit_status);
}

int	exec_left_right_pipe(t_exec_cmd *cmd, t_dlist *lst)
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
	{
		if (cmd->type != subs)
		{
			if (exec_left_right_pipe_cmd(cmd) != SUCCESS)
				full_exit(1);
		}
		else
			exec_left_right_pipe_subs(cmd);
	}
	add_pid(pid);
	close_fd(&cmd->pipe_fd[1]);
	return (SUCCESS);
}
