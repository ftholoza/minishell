/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:37:37 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 17:57:29 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_exec_cmd *cmd)
{
	t_dlist	*lst;
	t_env	*env;

	if (cmd->cmd->argc > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->cmd->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	lst = get_ms()->env;
	while (lst)
	{
		env = lst->data;
		if (env->name && env->value)
		{
			ft_printf("%s=%s\n", env->name, env->value);
		}
		lst = lst->next;
	}
	return (SUCCESS);
}
