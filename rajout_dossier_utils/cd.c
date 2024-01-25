/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:03:15 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 19:06:07 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_structs.h"

static int	control(t_cd *data)
{
	if (data->argc > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments", 2);
		free_struct_cd(data);
		return (0);
	}
	if (data->argc == 1)
	{
		if (simple_cd(data))
		{
			free_struct_cd(data);
			return (0);
		}
	}
	return (1);
}

int	cd(int argc, char **argv, t_dlist *env)
{
	t_cd	*data;

	data = init_data(argc, argv, env);
	if (!data)
		return (0);
	if (!control(data))
		return (1);
	if (absolut_path(data))
		return (1);
	if (relative_path(data))
		return (1);
	return (0);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_dlist	*env;
	char	*current;

	env = get_env(envp);
	cd (argc, argv, env);
	current = pwd(2);
	printf("%s\n", current);
	ft_dl_clear(&env, del);
}*/

/*int	wave(t_cd *data)
{
	char	*path;
	char	*home;
	char	*rest;
	char	*temp;

	if (data->argc == 2)
	{
		if (ft_strncmp(data->argv[1], "~", 1) == 0
			&& ft_strlen(data->argv[1]) == 1)
		{
			path = get_home_path(data);
			if (!path)
				return (0);
			ft_chdir(data, path);
			return (1);
		}
		else if (ft_strncmp(data->argv[1], "~", 1) == 0
			&& ft_strlen(data->argv[1]) > 1)
		{
			temp = get_home_path(data);
			home = ft_substr(temp, 0, 5);
			rest = ft_substr(data->argv[1], 1, ft_strlen(data->argv[1]));
			if (rest[0] != '/')
				home = ft_strjoin(home, "/");
			path = ft_strjoin(home, rest);
			ft_chdir(data, path);
			return (1);
		}
	}
	return (0);
}*/

/*int	come_back(t_cd *data)
{
	char	*back_path;

	if (data->argc == 2)
	{
		if (ft_strncmp(data->argv[1], "-", 1) == 0
			&& ft_strlen(data->argv[1]) == 1)
		{
			back_path = get_oldpwd_path(data);
			ft_chdir(data, back_path);
			return (1);
		}
	}
	return (0);
}*/