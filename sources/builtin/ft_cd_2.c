/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:44:35 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 14:08:59 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	options(char **args, t_cd *data, int i)
{
	char	*tmp;

	while (args[i])
	{
		if (ft_strncmp(args[i], ".", 2) == 0)
		{
			tmp = pwd();
			ft_chdir(data, tmp);
			free(tmp);
			i++;
		}
		else
		{
			if (ft_strncmp(args[i], "..", 3) == 0)
			{
				if (point_point(data) == FAILURE)
					return (FAILURE);
			}
			else
				if (enter_dir(args[i], data) == FAILURE)
					return (FAILURE);
			i++;
		}
	}
	return (SUCCESS);
}

int	wave_home(t_cd *data, char *home, int *exit)
{
	if (!home)
		return (FAILURE);
	if (ft_chdir(data, home) != SUCCESS)
	{
		*exit = FAILURE;
		free(home);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	free_all_cd(char **args, t_cd *data, int *exit, int val)
{
	int	temp;

	temp = val;
	*exit = val;
	free_struct_cd(data);
	return (ft_free(val, "s", args));
}

int	wave_path(t_cd *data, int *exit)
{
	char	**args;
	char	*home;

	args = ft_split(data->argv[1], '/');
	if (!args)
		return (err(NULL, "malloc error", ERR_MALLOC));
	if (args[0] && ft_strlen(args[0]) > 1)
	{
		path_error(args[0]);
		return (free_all_cd(args, data, exit, FAILURE));
	}
	home = get_home_path(data);
	if (!home)
		return (free_all_cd(args, data, exit, FAILURE));
	if (wave_home(data, home, exit) == FAILURE)
		return (free_all_cd(args, data, exit, FAILURE));
	if (options(args, data, 1) == FAILURE)
	{
		return (free_all_cd(args, data, exit, data->exit));
	}
	else
		return (free_all_cd(args, data, exit, data->exit));
}
