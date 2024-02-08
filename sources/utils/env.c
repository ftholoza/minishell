/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:43:00 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/21 13:43:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_env_array(char **env_array, t_dlist *env)
{
	t_env	*data;
	char	*tmp;
	int		i;

	i = 0;
	while (env)
	{
		data = env->data;
		tmp = ft_strjoin(data->name, "=");
		env_array[i] = ft_strjoin(tmp, data->value);
		if (tmp)
			free(tmp);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
}

char	**create_env_array(t_dlist *env)
{
	char	**env_array;
	int		len;

	len = 1;
	while (env)
	{
		len++;
		env = env->next;
	}
	env_array = malloc(sizeof(char *) * len);
	if (!env_array)
		return (err_null("minishell: malloc error"));
	return (env_array);
}

char	**env_to_array(void)
{
	t_ms	*ms;
	t_dlist	*env;
	char	**env_array;

	ms = get_ms();
	env = ms->env;
	env_array = create_env_array(env);
	if (env_array)
		populate_env_array(env_array, env);
	return (env_array);
}

char	*ft_getenv(char *name)
{
	t_ms	*ms;
	t_dlist	*lst;
	t_env	*env;

	ms = get_ms();
	lst = ms->env;
	while (lst)
	{
		env = lst->data;
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
