/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:29:22 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 16:38:59 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_cd(t_cd *data)
{
	char	*path;
	int		exit;

	if (data->argc == 1 || ft_strncmp(data->argv[1], "--", 3) == 0)
	{
		path = get_home_path(data);
		if (!path)
		{
			free_struct_cd(data);
			return (FAILURE);
		}
		if (ft_chdir(data, path) != FAILURE)
		{
			exit = data->exit;
			free_struct_cd(data);
			return (exit);
		}
		free_struct_cd(data);
	}
	return (FAILURE);
}

t_cd	*init_data(t_exec_cmd *cmd, t_dlist *env)
{
	t_cd	*data;
	char	*start;

	data = malloc(sizeof(t_cd));
	if (!data)
		return (err_null("minishell: malloc error"));
	ft_bzero(data, sizeof(t_cd));
	start = pwd();
	if (!start)
		return (err_null("minishell: malloc error"));
	data->argc = cmd->cmd->argc;
	data->argv = cmd->cmd->argv;
	data->env = env;
	data->start = start;
	data->exec = (cmd->left != piping && cmd->right != piping);
	data->silent = cmd->silent;
	data->is_change = 1;
	if (get_oldpwd_path(data))
		data->start_oldpwd = ft_strdup(get_oldpwd_path(data));
	data->is_change = 0;
	return (data);
}

static int	control(t_cd *data)
{
	if (data->argc > 2)
	{
		if (data->silent)
		{
			free_struct_cd(data);
			return (FAILURE);
		}
		free_struct_cd(data);
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	set_prev(t_exec_cmd *cmd, t_cd *data)
{
	char	*temp;

	temp = get_oldpwd_path(data);
	if (temp)
	{
		free(cmd->cmd->argv[1]);
		if (!cmd->silent)
			ft_putendl_fd(temp, 1);
		cmd->cmd->argv[1] = ft_strdup(temp);
		return (SUCCESS);
	}
	free_struct_cd(data);
	return (FAILURE);
}

int	ft_cd(t_exec_cmd *cmd)
{
	t_cd	*data;
	int		exit;

	data = init_data(cmd, get_ms()->env);
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	if (control(data) != SUCCESS)
		return (FAILURE);
	if (cmd->cmd->argc == 1 || ft_strncmp(cmd->cmd->argv[1], "--", 3) == 0)
		return (simple_cd(data));
	if (ft_strncmp(cmd->cmd->argv[1], "-", 2) == 0)
		if (set_prev(cmd, data) != SUCCESS)
			return (FAILURE);
	if (ft_strncmp(cmd->cmd->argv[1], "~", 1) == 0)
		if (wave_path(data, &exit) >= 0)
			return (exit);
	if (absolut_path(data, &exit) == SUCCESS)
		return (exit);
	else if (relative_path(data, &exit) == SUCCESS)
		return (exit);
	return (FAILURE);
}
