/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:41:34 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 12:04:55 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_exec_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (cmd->cmd->argc <= 0)
		return (0);
	if (ft_strncmp(cmd->cmd->argv[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd->argv[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void	pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
		int (*builtin)(t_exec_cmd *))
{
	if (cmd->left == piping && cmd->right == piping)
		exec_left_right_pipe_builtin(cmd, lst, builtin);
	else if (cmd->right == piping)
		exec_right_pipe_builtin(cmd, lst, builtin);
	else if (cmd->left == piping)
		exec_left_pipe_builtin(cmd, lst, builtin);
	else
		exec_no_pipe_builtin(cmd, lst, builtin);
}

void	pipe_and_exec(t_exec_cmd *cmd, t_dlist *lst,
		int (*builtin)(t_exec_cmd *cmd))
{
	int	return_value;

	pipe_builtin(cmd, lst, builtin);
	cmd->silent = 1;
	return_value = builtin(cmd);
	update_exit(cmd, return_value);
}

void	exec_builtin(t_exec_cmd *cmd, t_dlist *lst)
{
	if (ft_strncmp(cmd->cmd->argv[0], "cd", 3) == 0)
		pipe_and_exec(cmd, lst, &ft_cd);
	else if (ft_strncmp(cmd->cmd->argv[0], "echo", 5) == 0)
		pipe_builtin(cmd, lst, &ft_echo);
	else if (ft_strncmp(cmd->cmd->argv[0], "pwd", 4) == 0)
		pipe_builtin(cmd, lst, &ft_pwd);
	else if (ft_strncmp(cmd->cmd->argv[0], "env", 4) == 0)
		pipe_builtin(cmd, lst, &ft_env);
	else if (ft_strncmp(cmd->cmd->argv[0], "export", 7) == 0)
		pipe_and_exec(cmd, lst, &ft_export);
	else if (ft_strncmp(cmd->cmd->argv[0], "unset", 6) == 0)
		pipe_and_exec(cmd, lst, &ft_unset);
	else if (ft_strncmp(cmd->cmd->argv[0], "exit", 5) == 0)
		pipe_and_exec(cmd, lst, ft_exit);
}
