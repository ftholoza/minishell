/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:45:00 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 14:29:47 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	if (len < 1)
		return (0);
	i = 0;
	if (!(ft_isdigit(str[i]) || (str[i] == '+' && len != 1)
			|| (str[i] == '-' && len != 1)))
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (str[0] != '-' && ft_strncmp(str, "9223372036854775807", 20) > 0)
		return (0);
	if (str[0] == '-' && ft_strncmp(str, "-9223372036854775808", 21) > 0)
		return (0);
	return (1);
}

int	ft_exit(t_exec_cmd *cmd)
{
	if (!cmd->silent && !cmd->parent->parent)
		ft_putstr_fd("exit\n", 1);
	if (cmd->cmd->argc > 1 && !is_valid_number(cmd->cmd->argv[1]))
	{
		if (cmd->silent)
			full_exit(2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		full_exit(2);
	}
	if (cmd->cmd->argc > 2)
	{
		if (cmd->silent)
			return (FAILURE);
		err("exit", "too many arguments", FAILURE);
		return (FAILURE);
	}
	if (cmd->cmd->argc == 2)
		full_exit(ft_atoi(cmd->cmd->argv[1]));
	full_exit(SUCCESS);
	return (SUCCESS);
}
