/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:09:24 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 17:27:29 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	name = ft_substr(arg, 0, i);
	return (name);
}

char	*extract_value(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	value = ft_substr(arg, i + 1, ft_strlen(arg));
	if (ft_strlen(value) == 0)
	{
		value[0] = 0;
		return (value);
	}
	return (value);
}

int	add_to_env(char *name, char *value)
{
	t_dlist	*new;
	t_env	*data;

	new = malloc(sizeof(*new) * 1);
	if (!new)
		return (err(NULL, "malloc error", ERR_MALLOC));
	new->next = NULL;
	data = malloc(sizeof(*data) * 1);
	if (!data)
	{
		free(new);
		return (err(NULL, "malloc error", ERR_MALLOC));
	}
	data->name = name;
	data->value = value;
	new->data = data;
	ft_dl_add_back(&get_ms()->env, new);
	return (SUCCESS);
}

int	sub_process_export(char *name, char *value, t_env *data)
{
	t_dlist	*temp;

	temp = get_ms()->env;
	while (temp != NULL)
	{
		data = temp->data;
		if (ft_strncmp(name, data->name, ft_strlen(name) - 1) == 0)
		{
			if (name[ft_strlen(name) - 1] == '+')
			{
				data->value = ft_str_append(data->value, value);
				ft_free(0, "vv", value, name);
				return (SUCCESS);
			}
			if (ft_strncmp(data->name, name, ft_strlen(data->name) + 1) == 0)
			{	
				ft_free(0, "vv", name, data->value);
				data->value = value;
				return (SUCCESS);
			}
		}
		temp = temp->next;
	}
	return (FAILURE);
}

int	trust_the_process(char *name, char *value)
{
	t_env	*data;
	char	*temp;

	data = NULL;
	if (sub_process_export(name, value, data) == SUCCESS)
		return (SUCCESS);
	if (name[ft_strlen(name) - 1] == '+')
	{
		temp = name;
		name = ft_substr(temp, 0, ft_strlen(temp) - 1);
		free(temp);
	}
	if (add_to_env(name, value) != SUCCESS)
		return (ERR_MALLOC);
	return (SUCCESS);
}
