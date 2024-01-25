/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:28:53 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 21:36:25 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	run_cmds(t_exec_cmd *cmd, t_dlist *lst)
{
	if (is_built_in(cmd))
		return ;
	if ((last_op(lst) == and && cmd->parent->exit_status == 0)
		|| (last_op(lst) == or && cmd->parent->exit_status != 0)
		|| last_op(lst) == none)
		execute_cmd(cmd, lst);
}*/

int	is_built_in(t_exec_cmd *cmd)
{
	char	*name;
	t_dlist	*env;
	t_env	*data;
	t_ms	*ms;

	ms = get_ms();
	env = ms->env;
	data = env->data;
	name = cmd->cmd->argv[0];
	if (ft_strncmp(name, "cd", ft_strlen(name)) == 0)
	{
		if (cd(cmd->cmd->argc, cmd->cmd->argv, env))
			return (1);
	}
	if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
	{
		if (ft_unset(cmd->cmd->argc, cmd->cmd->argv, env))
			return (1);
	}
	return (0);
}
