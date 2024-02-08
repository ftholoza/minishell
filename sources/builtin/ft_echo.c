/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:12:41 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 18:13:33 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_minus_n(char *str)
{
	int	i;

	if (ft_strlen(str) < 2)
		return (0);
	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo(t_exec_cmd *cmd)
{
	int	endl;
	int	i;

	i = 0;
	endl = 1;
	while (cmd->cmd->argv[++i])
	{
		if (is_minus_n(cmd->cmd->argv[i]))
			endl = 0;
		else
			break ;
	}
	i--;
	while (cmd->cmd->argv[++i])
	{
		ft_printf("%s", cmd->cmd->argv[i]);
		if (cmd->cmd->argv[i + 1])
			write(1, " ", 1);
	}
	if (endl)
		write(1, "\n", 1);
	full_exit(0);
	return (SUCCESS);
}
