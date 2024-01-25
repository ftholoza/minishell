/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:05:02 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 21:14:29 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_structs.h"

int	ft_chdir(t_cd *data, char *path)
{
	char	*temp;
	char	*current;

	temp = pwd(2);
	if (chdir(path) == 0)
	{
		change_oldpwd(data, temp);
		free(temp);
		change_pwd(data, path);
		return (1);
	}
	chdir(data->start);
	current = pwd(2);
	free(current);
	ft_putstr_fd("bash: cd: ", 2);
	perror(path);
	free(temp);
	return (0);
}

int	simple_cd(t_cd *data)
{
	char	*path;

	if (data->argc == 1)
	{
		path = get_home_path(data);
		if (!path)
			return (1);
		ft_chdir(data, path);
		return (1);
	}
	return (0);
}

int	absolut_path(t_cd *data)
{
	if (ft_strncmp(data->argv[1], "/", 1) == 0)
	{
		ft_chdir(data, data->argv[1]);
		free_struct_cd(data);
		return (1);
	}
	return (0);
}

t_cd	*init_data(int argc, char **argv, t_dlist *env)
{
	t_cd	*data;
	char	*start;

	data = malloc(sizeof(*data));
	if (!data)
		return (data);
	start = pwd(2);
	if (!start)
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->start = start;
	return (data);
}

void	free_struct_cd(t_cd *data)
{
	free(data->start);
	free(data);
}
