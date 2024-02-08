/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:58:22 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 15:51:57 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prev(char *paths)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	if (!paths)
		return (NULL);
	while (paths[i])
		i++;
	i--;
	while (paths[i] && paths[i] != '/')
		i--;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (err_null("minishell: malloc error"));
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
	if (!path)
		return (err_null("minishell: malloc error"));
	free(temp);
	temp = path;
	path = ft_strjoin(temp, name);
	if (!path)
		return (err_null("minishell: malloc error"));
	free(temp);
	return (path);
}

char	*pwd(void)
{
	char	*path;
	int		buf;

	buf = 64;
	path = malloc(sizeof(char) * buf);
	if (!path)
		return (err_null("minishell: malloc error"));
	while (!getcwd(path, buf))
	{
		free(path);
		buf += 64;
		path = malloc(sizeof(char) * buf);
		if (!path)
			return (err_null("minishell: malloc error"));
	}
	return (path);
}

int	enter_dir(char *name, t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd();
	temp = path;
	path = add_next(temp, name);
	if (!path)
		return (ERR_MALLOC);
	if (ft_chdir(data, path) != SUCCESS)
	{
		free(path);
		return (FAILURE);
	}
	free(path);
	return (SUCCESS);
}

void	free_struct_cd(t_cd *data)
{
	free(data->start);
	free(data->start_oldpwd);
	free(data);
}
