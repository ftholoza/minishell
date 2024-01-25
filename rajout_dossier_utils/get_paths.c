/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:45 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 19:06:32 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_structs.h"

char	*get_home_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!data->env)
		return (NULL);
	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "HOME", 5) == 0)
		{
			res = dataenv->value;
			if (!res)
				return (NULL);
			return (res);
		}
		temp = temp->next;
	}
	write(2, "bash: cd: HOME not set\n", 23);
	return (NULL);
}

char	*get_oldpwd_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!data->env)
		return (NULL);
	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "OLDPWD", 7) == 0)
		{
			res = dataenv->value;
			if (!res)
				return (NULL);
			return (res);
		}
		temp = temp->next;
	}
	write(2, "bash: cd: OLDPWD not set\n", 25);
	return (NULL);
}

char	*prev(char *paths)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	if (!paths)
		return (paths);
	while (paths[i])
		i++;
	i--;
	while (paths[i] != '/' && paths[i])
		i--;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (res);
	res[i] = 0;
	while (j != i)
	{
		res[j] = paths[j];
		j++;
	}
	free(paths);
	return (res);
}

char	*add_next(char	*path, char	*name)
{
	char	*temp;

	temp = path;
	path = ft_strjoin(temp, "/");
	free(temp);
	temp = path;
	path = ft_strjoin(temp, name);
	free(temp);
	return (path);
}
