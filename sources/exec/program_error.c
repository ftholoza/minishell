/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:32:27 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 14:32:36 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_such_file(t_exec_cmd *cmd)
{
	ft_putstr_fd(cmd->cmd->argv[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	full_exit(127);
}

void	permission_denied(t_exec_cmd *cmd)
{
	ft_putstr_fd(cmd->cmd->argv[0], 2);
	ft_putendl_fd(": Permission denied", 2);
	full_exit(126);
}

void	command_not_found(t_exec_cmd *cmd)
{
	if (cmd->cmd->argv[0][0] == 0)
		ft_putstr_fd("''", 2);
	ft_putstr_fd(cmd->cmd->argv[0], 2);
	ft_putendl_fd(": command not found", 2);
	full_exit(127);
}

void	filename_arg(t_exec_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd->argv[0], 2);
	ft_putendl_fd(": filename argument required", 2);
	full_exit(2);
}
