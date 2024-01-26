/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:15:42 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/26 19:40:06 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_home_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!data->env)
		return (err_null("ENV ERROR\n"));
	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "HOME", 5) == 0)
		{
			res = dataenv->value;
			if (!res)
				return (err_null("minishell: cd: HOME not set"));
			return (res);
		}
		temp = temp->next;
	}
	return (err_null("minishell: cd: HOME not set"));
}

char	*get_oldpwd_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!data->env)
		return (NULL);
	temp = data->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "OLDPWD", 7) == 0)
		{
			res = dataenv->value;
			if (!res)
				return (err_null("bash: cd: OLDPWD not set\n"));
			return (res);
		}
		temp = temp->next;
	}
	return (err_null("bash: cd: OLDPWD not set\n"));
}

char	*prev(char *paths)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	if (!paths)
		return (NULL);
	while (paths[i])
		i++;
	i--;
	while (paths[i] && paths[i] != '/')
		i--;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (err_null("minishell: cd: malloc error\n"));
	res[i] = 0;
	while (j != i)
	{
		res[j] = paths[j];
		j++;
	}
	free(paths);
	return (res);
}

char	*add_next(char	*path, char	*name)
{
	char	*temp;

	temp = path;
	path = ft_strjoin(temp, "/");
	if (!path)
		return (err_null("minishell: malloc error\n"));
	free(temp);
	temp = path;
	path = ft_strjoin(temp, name);
	if (!path)
		return (err_null("minishell: malloc error\n"));
	free(temp);
	return (path);
}

int	change_pwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	temp = data->env;
	if (!temp)
		return (err("minishell: env error\n", ERR_ENV));
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (!dataenv->name)
			return (ERR_ENV);
		if (ft_strncmp(dataenv->name, "PWD", 3) == 0
			&& ft_strlen(dataenv->name) == 3)
		{
			free(dataenv->value);
			dataenv->value = ft_strdup(new);
			if (!dataenv->value)
				return (err("minishell: malloc error\n", ERR_MALLOC));
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (ERR_ENV);
}

int	change_oldpwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	temp = data->env;
	if (!temp)
		return (err("minishell: env error\n", ERR_ENV));
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (!dataenv->name)
			return (ERR_ENV);
		if (ft_strncmp(dataenv->name, "OLDPWD", 6) == 0
			&& ft_strlen(dataenv->name) == 6)
		{
			free(dataenv->value);
			dataenv->value = ft_strdup(new);
			if (!dataenv->value)
				return (err("minishell: malloc error\n", ERR_MALLOC));
			return (SUCCESS);
		}
		temp = temp->next;
	}
	return (ERR_ENV);
}

char	*pwd(void)
{
	char	*path;
	int		buf;

	buf = 64;
	path = malloc(sizeof(char) * buf);
	if (!path)
		return (err_null("minishell: malloc error\n"));
	while (!getcwd(path, buf))
	{
		free(path);
		buf += 64;
		path = malloc(sizeof(char) * buf);
		if (!path)
			return (err_null("minishell: malloc error\n"));
	}
	return (path);
}

static int	point_point(t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd();
	if (!path)
		return (err("minishell: malloc error\n", ERR_MALLOC));
	temp = path;
	path = prev(temp);
	if (!path)
		return (err("minishell: malloc error\n", ERR_MALLOC));
	if (ft_strlen(path) == 0)
	{
		free(path);
		if (ft_chdir(data, "/") != SUCCESS)
			return (ERR_ENV);
		return (SUCCESS);
	}
	if (ft_chdir(data, path) == SUCCESS)
	{
		free(path);
		return (SUCCESS);
	}
	free(path);
	return (FAILURE);
}

static int	enter_dir(char *name, t_cd *data)
{
	char	*path;
	char	*temp;

	path = pwd();
	temp = path;
	path = add_next(temp, name);
	if (!path)
		return (ERR_MALLOC);
	if (ft_chdir(data, path) != SUCCESS)
	{
		free(path);
		return (FAILURE);
	}
	free(path);
	return (SUCCESS);
}

static int	options(char **args, t_cd *data)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ".", 1) == 0
			&& ft_strlen(args[i]) == 1)
			i++;
		else
		{
			if (ft_strncmp(args[i], "..", 2) == 0
				&& ft_strlen(args[i]) == 2)
			{
				if (point_point(data) == FAILURE)
					return (FAILURE);
			}
			else
			{
				if (enter_dir(args[i], data) == FAILURE)
					return (FAILURE);
			}
			i++;
		}
	}
	return (SUCCESS);
}

int	relative_path(t_cd *data)
{
	char	**args;

	args = ft_split(data->argv[1], '/');
	if (!args)
		return (err("minishell: malloc error", ERR_MALLOC));
	if (options(args, data) == FAILURE)
	{
		free_tab(args);
		free_struct_cd(data);
		return (FAILURE);
	}
	free_tab(args);
	free_struct_cd(data);
	return (SUCCESS);
}

int	ft_chdir(t_cd *data, char *path)
{
	char	*temp;

	temp = pwd();
	if (chdir(path) == 0)
	{
		change_oldpwd(data, temp);
		free(temp);
		change_pwd(data, path);
		return (SUCCESS);
	}
	chdir(data->start);
	free(temp);
	perror("cd");
	return (FAILURE);
}

int	simple_cd(t_cd *data)
{
	char	*path;

	if (data->argc == 1)
	{
		path = get_home_path(data);
		if (!path)
			return (ERR_ENV);
		if (ft_chdir(data, path) != FAILURE)
		{
			free_struct_cd(data);
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

int	absolut_path(t_cd *data)
{
	if (ft_strncmp(data->argv[1], "/", 1) == 0)
	{
		if (ft_chdir(data, data->argv[1]) != SUCCESS)
			return (SUCCESS);
		free_struct_cd(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

t_cd	*init_data(int argc, char **argv, t_dlist *env)
{
	t_cd	*data;
	char	*start;

	data = malloc(sizeof(*data));
	if (!data)
		return (err_null("minishell: malloc error"));
	start = pwd();
	if (!start)
		return (err_null("minishell: malloc error"));
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->start = start;
	return (data);
}

void	free_struct_cd(t_cd *data)
{
	free(data->start);
	free(data);
}

static int	control(t_cd *data)
{
	if (data->argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		free_struct_cd(data);
		return (err("minishell: cd: arguments error\n", FAILURE));
	}
	return (SUCCESS);
}

int	cd(int argc, char **argv, t_dlist *env)
{
	t_cd	*data;

	data = init_data(argc, argv, env);
	if (!data)
		return (err("minishell: malloc error", ERR_MALLOC));
	if (control(data) != SUCCESS)
		return (FAILURE);
	if (argc == 1)
	{
		simple_cd(data);
		return (SUCCESS);
	}
	if (absolut_path(data) == SUCCESS)
		return (SUCCESS);
	else if (relative_path(data) != SUCCESS)
		return (SUCCESS);
	return (SUCCESS);
}
