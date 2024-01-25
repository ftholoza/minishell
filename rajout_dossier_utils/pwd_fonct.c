/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_fonct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:52:20 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 20:24:12 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_structs.h"

int	change_pwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "PWD", 3) == 0)
		{
			free(dataenv->value);
			dataenv->value = ft_strdup(new);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	change_oldpwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "OLDPWD", 6) == 0)
		{
			free(dataenv->value);
			dataenv->value = ft_strdup(new);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*pwd(int argc)
{
	char	*path;
	int		buf;

	if (argc != 2)
	{
		write(1, "Too many arguments", 19);
		return (NULL);
	}
	buf = 64;
	path = malloc(sizeof(char) * buf);
	while (!getcwd(path, buf))
	{
		free(path);
		buf += 64;
		path = malloc(sizeof(char) * buf);
	}
	return (path);
}
