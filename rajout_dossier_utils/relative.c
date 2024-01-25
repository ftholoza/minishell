/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:16:39 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 18:01:09 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_structs.h"

static int	point_point(t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd(2);
	temp = path;
	path = prev(temp);
	if (ft_strlen(path) == 0)
	{
		free(path);
		ft_chdir(data, "/");
		return (1);
	}
	ft_chdir(data, path);
	free(path);
	return (1);
}

static int	enter_dir(char *name, t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd(2);
	temp = path;
	path = add_next(temp, name);
	ft_chdir(data, path);
	free(path);
	return (0);
}

static int	options(char **args, t_cd *data)
{
	int		i;
	char	*path;

	i = 0;
	path = pwd(2);
	while (args[i])
	{
		if (ft_strncmp(args[i], ".", 1) == 0
			&& ft_strlen(args[i]) == 1)
			i++;
		else
		{
			if (ft_strncmp(args[i], "..", 2) == 0
				&& ft_strlen(args[i]) == 2)
				point_point(data);
			else
				if (!enter_dir(args[i], data))
					break ;
			i++;
		}
	}
	free(path);
	return (1);
}

int	relative_path(t_cd *data)
{
	char	**args;

	args = ft_split(data->argv[1], '/');
	if (!args)
		return (0);
	options(args, data);
	free_tab(args);
	free_struct_cd(data);
	return (1);
}
