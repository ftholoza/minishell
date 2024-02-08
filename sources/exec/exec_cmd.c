/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:18:32 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 16:44:21 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	if (*fd != 0)
	{
		close(*fd);
		*fd = 0;
	}
}

void	close_fds(t_dlist *lst)
{
	while (lst)
	{
		close_fd(&((t_exec_cmd *)lst->data)->pipe_fd[0]);
		close_fd(&((t_exec_cmd *)lst->data)->pipe_fd[1]);
		lst = lst->next;
	}
}

int	close_fds_err(t_dlist *lst)
{
	close_fds(lst);
	return (err(NULL, "unable to fork", ERR_FORK));
}

void	exec_prog(t_exec_cmd *cmd)
{
	char	*prog;
	char	**env;
	int		perm_denied;

	if (cmd->cmd->argc == 0)
		full_exit(SUCCESS);
	prog = get_prog(cmd->cmd->argv[0], &perm_denied);
	if (!prog && !perm_denied)
		command_not_found(cmd);
	else if (!prog && perm_denied == 1)
		permission_denied(cmd);
	else if (!prog && perm_denied == 2)
		no_such_file(cmd);
	else if (!prog && perm_denied == 3)
		filename_arg(cmd);
	if (check_type(prog, dir))
	{
		err(prog, "Is a directory", FAILURE);
		free(prog);
		full_exit(126);
	}
	env = env_to_array();
	execve(prog, cmd->cmd->argv, env);
}

int	execute_cmd(t_exec_cmd *cmd, t_dlist *lst)
{
	if (cmd->left == piping && cmd->right == piping)
	{
		if (exec_left_right_pipe(cmd, lst) != SUCCESS)
			return (ERR_FORK);
	}
	else if (cmd->right == piping)
	{
		if (exec_right_pipe(cmd, lst) != SUCCESS)
			return (ERR_FORK);
	}
	else if (cmd->left == piping)
	{
		if (exec_left_pipe(cmd, lst) != SUCCESS)
			return (ERR_FORK);
	}
	else
	{
		if (exec_no_pipe(cmd, lst) != SUCCESS)
			return (ERR_FORK);
	}
	return (SUCCESS);
}
