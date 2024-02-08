/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_no_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:18:11 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 11:39:48 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_no_pipe_b(t_exec_cmd *cmd, int (*builtin)(t_exec_cmd *))
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			full_exit(FAILURE);
	dup2(cmd->in_fd, 0);
	dup2(cmd->out_fd, 1);
	full_exit(builtin(cmd));
}

int	exec_no_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
		int (*builtin)(t_exec_cmd *))
{
	pid_t	pid;
	int		exit_status;

	signal(SIGINT, &update_signal);
	cmd->in_fd = cmd->parent->in_fd;
	cmd->out_fd = cmd->parent->out_fd;
	pid = fork();
	if (pid < 0)
		return (close_fds_err(lst));
	if (!pid)
		exec_no_pipe_b(cmd, builtin);
	else
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			update_exit(cmd, WEXITSTATUS(exit_status));
		close_all_fds();
	}
	return (SUCCESS);
}
