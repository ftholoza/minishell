/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:04:22 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 16:46:32 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_path(char *path, char *str)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(path, "/");
	out = ft_strjoin(tmp, str);
	free(tmp);
	return (out);
}

char	*get_prog_path(char *name, char **split, int *perm_denied)
{
	char	*full;
	int		i;

	i = -1;
	while (split[++i])
	{
		full = add_path(split[i], name);
		if (check_exist(full))
		{
			if (check_perm(full, x))
			{
				ft_free(0, "s", split);
				return (full);
			}
			else
			{
				*perm_denied = 1;
				return (NULL);
			}
		}
		free(full);
	}
	ft_free(0, "s", split);
	return (NULL);
}

int	check_basics(char *name, int *perm_denied)
{
	if (name && ft_strncmp(name, ".", 2) == 0)
	{
		*perm_denied = 3;
		return (1);
	}
	else if (name && name[0] == 0)
		return (1);
	else if (name && ft_strncmp(name, "..", 3) == 0)
		return (1);
	return (0);
}

void	*perm_denied_2(int *perm_denied)
{
	*perm_denied = 2;
	return (NULL);
}

char	*get_prog(char *name, int *perm_denied)
{
	char	*paths;
	char	**split;

	*perm_denied = 0;
	if (check_basics(name, perm_denied))
		return (NULL);
	if (check_exist(name))
	{
		if (name[0] == '.' || name[0] == '/')
		{
			if (check_perm(name, x))
				return (ft_strdup(name));
			*perm_denied = 1;
			return (NULL);
		}
	}
	else if (name[0] == '.' || name[0] == '/')
		return (perm_denied_2(perm_denied));
	paths = ft_getenv("PATH");
	if (!paths)
		return (NULL);
	split = ft_split(paths, ':');
	return (get_prog_path(name, split, perm_denied));
}
