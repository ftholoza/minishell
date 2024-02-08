/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:50:11 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 16:47:07 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!get_ms()->env && data->silent == 0)
		return (err_null("minishell: cd: HOME not set"));
	temp = get_ms()->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "HOME", 5) == 0)
		{
			res = dataenv->value;
			if (res)
				return (res);
			else if (data->silent)
				return (NULL);
			return (err_null("minishell: cd: HOME not set"));
		}
		temp = temp->next;
	}
	if (data->silent)
		return (NULL);
	return (err_null("minishell: cd: HOME not set"));
}

char	*get_oldpwd_path(t_cd *data)
{
	t_dlist	*temp;
	t_env	*dataenv;
	char	*res;

	if (!get_ms()->env && data->silent == 0 && data->is_change == 0)
		return (err_null("minishell: cd: OLDPWD not set"));
	temp = get_ms()->env;
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (ft_strncmp(dataenv->name, "OLDPWD", 7) == 0)
		{
			res = dataenv->value;
			if (res)
				return (res);
			else if (data->silent)
				return (NULL);
			return (err_null("minishell: cd: OLDPWD not set"));
		}
		temp = temp->next;
	}
	if (data->silent || data->is_change == 1)
		return (NULL);
	return (err_null("minishell: cd: OLDPWD not set"));
}

int	change_var_pwd(t_env *dataenv, char *new)
{
	free(dataenv->value);
	dataenv->value = ft_strdup(new);
	if (!dataenv->value)
		return (err(NULL, "malloc error", ERR_MALLOC));
	return (SUCCESS);
}

int	change_pwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	(void)data;
	temp = get_ms()->env;
	if (!temp)
	{
		add_to_env(ft_strdup("PWD"), pwd());
		return (ERR_ENV);
	}
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (!dataenv->name)
			return (ERR_ENV);
		if (ft_strncmp(dataenv->name, "PWD", 4) == 0)
			return (change_var_pwd(dataenv, new));
		temp = temp->next;
	}
	add_to_env(ft_strdup("PWD"), pwd());
	return (ERR_ENV);
}

int	change_oldpwd(t_cd *data, char *new)
{
	t_dlist	*temp;
	t_env	*dataenv;

	(void)data;
	temp = get_ms()->env;
	if (!temp)
	{
		add_to_env(ft_strdup("OLDPWD"), pwd());
		return (ERR_ENV);
	}
	while (temp != NULL)
	{
		dataenv = temp->data;
		if (!dataenv->name)
			return (ERR_ENV);
		if (ft_strncmp(dataenv->name, "OLDPWD", 7) == 0)
			return (change_var_pwd(dataenv, new));
		temp = temp->next;
	}
	add_to_env(ft_strdup("OLDPWD"), pwd());
	return (ERR_ENV);
}
