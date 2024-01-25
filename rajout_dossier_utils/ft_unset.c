/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:16:09 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 21:27:40 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(void *temp)
{
	t_env	*data;

	data = (t_env *)temp;
	free(data->name);
	free(data->value);
	free(data);
}

int	ft_unset(int argc, char **argv, t_dlist *env)
{
	t_env	*data;
	t_dlist	*temp;
	char	*name;

	temp = env;
	name = argv[1];
	if (argc != 2)
		return (0);
	while (temp != NULL)
	{
		data = temp->data;
		if (ft_strncmp(data->name, name, ft_strlen(data->name)) == 0)
		{
			ft_dl_remove_from(&env, temp, del_env);
			return (1);
		}
		temp = temp->next;
	}
	return (1);
}
