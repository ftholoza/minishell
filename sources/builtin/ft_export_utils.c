/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:54:30 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 14:30:59 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (0);
	if (arg[0] == '=')
		return (0);
	return (1);
}

int	check_plus(char	*arg, int i)
{
	if (arg[i])
	{
		if (arg[i] == '+')
		{
			i++;
			if (arg[i] && arg[i] == '=')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	err_not_valid(char *str, t_exec_cmd *cmd)
{
	if (cmd->silent)
		return (FAILURE);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (FAILURE);
}

int	ft_is_forbidden(char c)
{
	if (c >= 33 && c <= 47)
		return (1);
	if (c >= 58 && c <= 64)
		return (1);
	if (c >= 91 && c <= 96 && c != 95)
		return (1);
	if (c >= 123)
		return (1);
	return (0);
}
