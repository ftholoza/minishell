/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:43:10 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 17:02:05 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*get_ms(void)
{
	static t_ms	minishell;

	return (&minishell);
}

t_cmds	*get_cmds(void)
{
	t_ms	*ms;

	ms = get_ms();
	return (&ms->cmds);
}

int	init_env(char **env, t_ms *ms)
{
	int		i;
	int		j;
	char	**env_split;
	t_env	*new_env;

	i = -1;
	while (env[++i])
	{
		env_split = ft_split(env[i], '=');
		j = 0;
		while (env_split[j])
			j++;
		new_env = malloc(sizeof(t_env));
		if (!new_env)
		{
			ft_free(1, "s", env_split);
			return (err(NULL, "malloc error", ERR_MALLOC));
		}
		new_env->name = ft_strdup(env_split[0]);
		new_env->value = ft_substr(env[i], ft_strlen(env_split[0]) + 1,
				ft_strlen(env[i]));
		ft_free(1, "s", env_split);
		ft_dl_add_back(&ms->env, ft_dl_new(new_env));
	}
	return (SUCCESS);
}

char	*get_curr_dir(void)
{
	char	*path;
	int		buf;

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

int	init_minishell(char **env)
{
	t_ms	*ms;

	ms = get_ms();
	ft_bzero(ms, sizeof(t_ms));
	if (init_env(env, ms) != SUCCESS)
		return (ERR_ENV);
	ms->curr_dir = get_curr_dir();
	return (SUCCESS);
}
