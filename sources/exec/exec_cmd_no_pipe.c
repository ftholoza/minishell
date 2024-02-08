/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_no_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:20:50 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 16:37:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_no_pipe_cmd(t_exec_cmd *cmd)
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			return (ERR_FILE);
	dup2(cmd->in_fd, 0);
	dup2(cmd->out_fd, 1);
	exec_prog(cmd);
	return (SUCCESS);
}

void	exec_no_pipe_subs(t_exec_cmd *cmd)
{
	dup2(cmd->in_fd, 0);
	exec_shell(cmd);
	close_all_fds();
	full_exit(cmd->exit_status);
}

void	add_pid(pid_t pid)
{
	int	i;

	i = 0;
	while (get_ms()->pids[i] != 0)
		i++;
	get_ms()->pids[i] = pid;
}

int	exec_no_pipe(t_exec_cmd *cmd, t_dlist *lst)
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
	{
		if (cmd->type == subs)
			exec_no_pipe_subs(cmd);
		else
			if (exec_no_pipe_cmd(cmd) != SUCCESS)
				full_exit(1);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			update_exit(cmd, WEXITSTATUS(exit_status));
		close_all_fds();
	}
	return (SUCCESS);
}
