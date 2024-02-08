/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_left_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:19:10 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 11:58:36 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_left_pipe_cmd(t_exec_cmd *cmd)
{
	signal(SIGINT, &handle_child_signal);
	signal(SIGQUIT, SIG_IGN);
	if (cmd->cmd->redir)
		if (process_redir(cmd) != SUCCESS)
			return (ERR_FILE);
	dup2(cmd->in_fd, 0);
	dup2(cmd->parent->out_fd, 1);
	exec_prog(cmd);
	return (SUCCESS);
}

void	exec_left_pipe_subs(t_exec_cmd *cmd)
{
	dup2(cmd->in_fd, 0);
	exec_shell(cmd);
	close_all_fds();
	full_exit(cmd->exit_status);
}

void	wait_childs(t_exec_cmd *cmd)
{
	int		exit_status;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (get_ms()->pids[++i] != 0)
		len++;
	while (len >= 0)
	{
		waitpid(get_ms()->pids[len], &exit_status, 0);
		if (WIFEXITED(exit_status) && len == i - 1)
			update_exit(cmd, WEXITSTATUS(exit_status));
		len--;
		close_all_fds();
	}
}

int	exec_left_pipe(t_exec_cmd *cmd, t_dlist *lst)
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
	{
		if (cmd->type == subs)
			exec_left_pipe_subs(cmd);
		else
			if (exec_left_pipe_cmd(cmd) != SUCCESS)
				full_exit(1);
	}
	else
	{
		add_pid(pid);
		wait_childs(cmd);
		close_fds(lst);
	}
	return (SUCCESS);
}
