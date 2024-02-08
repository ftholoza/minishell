/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:06:36 by ftholoza          #+#    #+#             */
/*   Updated: 2024/02/06 20:22:01 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_not_valid_unset(char *str, t_exec_cmd *cmd)
{
	if (cmd->silent)
		return (FAILURE);
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" invalid parameter name", 2);
	return (FAILURE);
}

int	unset_name(char	*name, t_dlist *env)
{
	t_env	*data;
	t_dlist	*temp;

	temp = get_ms()->env;
	while (temp != NULL)
	{
		data = temp->data;
		if (ft_strncmp(name, data->name, ft_strlen(name) + 1) == 0)
		{
			ft_dl_remove_from(&env, temp, &free_env);
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_unset(t_exec_cmd *cmd)
{
	t_dlist	*env;
	int		i;

	i = 1;
	env = get_ms()->env;
	if (!env)
		return (FAILURE);
	if (cmd->cmd->argc < 2)
		return (0);
	if (cmd->left == piping || cmd->right == piping)
		return (SUCCESS);
	while (i < cmd->cmd->argc)
	{
		if (unset_name(cmd->cmd->argv[i], env) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
