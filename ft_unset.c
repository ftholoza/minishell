/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:06:36 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/29 10:28:49 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_name(char	*name, t_dlist *env)
{
	t_env	*data;
	t_dlist	*temp;

	temp = env;
	while (temp != NULL)
	{
		data = temp->data;
		if (ft_strncmp(name, data->name, ft_strlen(name) + 1) == 0)
		{
			if (ft_dl_remove_from(&env, temp, &free_env) == NULL)
				return (FAILURE);
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
	while (i < cmd->cmd->argc)
	{
		if (unset_name(cmd->cmd->argv[i], env) != SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
