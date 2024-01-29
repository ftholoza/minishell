/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:34:29 by francesco         #+#    #+#             */
/*   Updated: 2024/01/29 09:39:40 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (0);
	if (arg[0] == '=')
		return (0);
	return (1);
}

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

int add_to_env(t_dlist *env, char *name, char *value)
{
	t_dlist	*new;
	t_env	*data;

	new = malloc(sizeof(*new) * 1);
	if (!new)
		return (err("minishell: malloc error", ERR_MALLOC));
	new->next = NULL;
	data = malloc(sizeof(*data) * 1);
	if (!data)
	{
		free(new);
		return (err("minishell: malloc error", ERR_MALLOC));
	}
	data->name = name;
	data->value = value;
	new->data = data;
	ft_dl_add_back(&env, new);
	return (SUCCESS);
}

int trust_the_process(t_dlist *env, char *name, char *value)
{
	t_dlist	*temp;
	t_env	*data;

	temp = env;
	while (temp != NULL)
	{
		data = temp->data;
		if (ft_strncmp(name, data->name, ft_strlen(name) + 1) == 0)
		{
			free(name);
			free(data->value);
			data->value = value;
			return (SUCCESS);
		}
		temp = temp->next;
	}
	if (add_to_env(env, name, value) != SUCCESS)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	err_not_valid(char *str)
{
	write(2, "minishell: export: ", 20);
	ft_putstr_fd(str, 2);
	write(2, " not a valid identifier\n", 25);
	return (FAILURE);
}

int	check_char(t_exec_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < cmd->cmd->argc)
	{
		while (cmd->cmd->argv[i][j])
		{
			if (j == 0 && ft_isdigit(cmd->cmd->argv[i][j]))
				return (err_not_valid(cmd->cmd->argv[i]));
			if (!ft_isprint(cmd->cmd->argv[i][j]))
				return (err_not_valid(cmd->cmd->argv[i]));
			if (cmd->cmd->argv[i][j] == '[' || cmd->cmd->argv[i][j] == ']')
				return (err_not_valid(cmd->cmd->argv[i]));
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	check_all_args(t_exec_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (check_char(cmd) != SUCCESS)
		return (FAILURE);
	while (i < cmd->cmd->argc)
	{
		if (cmd->cmd->argv[i][0] == '=')
		{
			if (ft_strlen(cmd->cmd->argv[i]) == 1)
				return (err("minishell: bad assignement", FAILURE));
			write(2, "minishell: export:", 18);
			while (cmd->cmd->argv[i][j])
			{
				write(2, &cmd->cmd->argv[i][j], 1);
				j++;
			}
			write(2, " not a valid identifer\n", 23);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	start_the_process(t_exec_cmd *cmd)
{
	int		i;
	char	*name;
	char	*value;
	t_dlist	*env;

	i = 1;
	env = get_ms()->env;
	while (i < cmd->cmd->argc)
	{
		if (check_arg(cmd->cmd->argv[i]))
		{
			name = extract_name(cmd->cmd->argv[i]);
			if (!name)
				return (FAILURE);
			value = extract_value(cmd->cmd->argv[i]);
			if (!value)
				return (FAILURE);
			if (trust_the_process(env, name, value) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int ft_export(t_exec_cmd *cmd)
{
	if (cmd->cmd->argc < 2)
	{
		ft_env(cmd);
		return (SUCCESS);
	}
	if (check_all_args(cmd) != SUCCESS)
		return (FAILURE);
	if (start_the_process(cmd) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
