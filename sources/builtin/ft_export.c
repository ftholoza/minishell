/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:34:29 by francesco         #+#    #+#             */
/*   Updated: 2024/02/08 10:25:49 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_all_args(char *arg, t_exec_cmd *cmd)
{
	int	j;
	int	is_error;

	j = 0;
	is_error = 0;
	if (ft_isdigit(arg[0]) == 2048 || arg[0] == '=' || arg[0] == '+'
		|| ft_isspace(arg[0]))
		return (err_not_valid(arg, cmd));
	while (arg[j])
	{
		if (arg[j] == '=')
		{
			is_error = 1;
			while (arg[j])
				j++;
		}
		if (!check_plus(arg, j))
			if (ft_is_forbidden(arg[j]))
				return (err_not_valid(arg, cmd));
		if (arg[j])
			j++;
	}
	if (is_error == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	check_all_args_silence(char *arg)
{
	int	j;
	int	is_error;

	j = 0;
	is_error = 0;
	if (ft_isdigit(arg[0]) == 2048)
		return (FAILURE);
	if (arg[0] == '=' || arg[0] == '+' || ft_isspace(arg[0]))
		return (FAILURE);
	while (arg[j])
	{
		if (arg[j] == '=')
		{
			while (arg[j])
				j++;
		}
		if (!check_plus(arg, j))
			if (ft_is_forbidden(arg[j]))
				return (FAILURE);
		if (arg[j])
			j++;
	}
	return (SUCCESS);
}

int	start_the_process(t_exec_cmd *cmd)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (cmd->left == piping || cmd->right == piping)
		return (SUCCESS);
	while (i < cmd->cmd->argc)
	{
		if (check_all_args(cmd->cmd->argv[i], cmd) == SUCCESS)
		{
			name = extract_name(cmd->cmd->argv[i]);
			if (!name)
				return (FAILURE);
			value = extract_value(cmd->cmd->argv[i]);
			if (!value)
				return (FAILURE);
			if (trust_the_process(name, value) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	no_arg(t_exec_cmd *cmd)
{
	t_dlist	*lst;
	t_env	*env;

	(void)cmd;
	lst = get_ms()->env;
	while (lst)
	{
		env = lst->data;
		if (env->name && env->value && !cmd->silent)
			ft_printf("declare -x %s=\"%s\"\n", env->name, env->value);
		lst = lst->next;
	}
	return (SUCCESS);
}

int	ft_export(t_exec_cmd *cmd)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (cmd->cmd->argc < 2)
		return (no_arg(cmd));
	while (cmd->cmd->argv[i])
	{
		if (check_all_args_silence(cmd->cmd->argv[i]) != SUCCESS)
			error = 1;
		i++;
	}
	start_the_process(cmd);
	if (error > 0)
		return (FAILURE);
	return (SUCCESS);
}
