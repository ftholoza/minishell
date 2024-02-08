/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:53:50 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 15:51:30 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	point_point(t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd();
	if (!path)
		return (err(NULL, "malloc error", ERR_MALLOC));
	temp = path;
	path = prev(temp);
	if (!path)
		return (err(NULL, "malloc error", ERR_MALLOC));
	if (ft_strlen(path) == 0)
	{
		free(path);
		if (ft_chdir(data, "/") != SUCCESS)
			return (ERR_ENV);
		return (SUCCESS);
	}
	if (ft_chdir(data, path) == SUCCESS)
	{
		free(path);
		return (SUCCESS);
	}
	free(path);
	return (FAILURE);
}

int	relative_path(t_cd *data, int *exit)
{
	char	**args;

	args = ft_split(data->argv[1], '/');
	if (!args)
		return (err(NULL, "malloc error", ERR_MALLOC));
	if (options(args, data, 0) == FAILURE)
	{
		ft_free(0, "s", args);
		*exit = data->exit;
		free_struct_cd(data);
		return (FAILURE);
	}
	ft_free(0, "s", args);
	*exit = data->exit;
	free_struct_cd(data);
	return (SUCCESS);
}

int	path_error(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (FAILURE);
	while (path[i])
		i++;
	i--;
	while (i >= 0 && path[i] != '/')
		i--;
	i++;
	ft_putstr_fd("minishell: cd: ", 2);
	while (path[i])
	{
		write(2, &path[i], 1);
		i++;
	}
	ft_putendl_fd(": No such file or directory", 2);
	return (SUCCESS);
}

int	ft_chdir(t_cd *data, char *path)
{
	char	*temp;

	temp = pwd();
	if (chdir(path) == 0)
	{
		if (data->exec)
		{
			change_oldpwd(data, data->start);
			free(temp);
			change_pwd(data, path);
		}
		else
			chdir(temp);
		data->exit = 0;
		return (SUCCESS);
	}
	chdir(data->start);
	change_oldpwd(data, data->start_oldpwd);
	free(temp);
	if (!data->silent)
		path_error(path);
	data->exit = 1;
	return (FAILURE);
}

int	absolut_path(t_cd *data, int *exit)
{
	if (!data)
		return (FAILURE);
	if (ft_strncmp(data->argv[1], "/", 1) == 0)
	{
		ft_chdir(data, data->argv[1]);
		*exit = data->exit;
		free_struct_cd(data);
		return (SUCCESS);
	}
	return (FAILURE);
}
