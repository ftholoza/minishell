/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:25:47 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 15:07:52 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_no_cmd(void)
{
	char	*path;
	int		buf;

	buf = 64;
	path = malloc(sizeof(char) * buf);
	if (!path)
		return (err(NULL, "malloc error", FAILURE));
	while (!getcwd(path, buf))
	{
		free(path);
		buf += 64;
		path = malloc(sizeof(char) * buf);
		if (!path)
			return (err(NULL, "malloc error", FAILURE));
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (SUCCESS);
}

int	ft_pwd(t_exec_cmd *cmd)
{
	char	*path;
	int		buf;

	(void)cmd;
	buf = 64;
	path = malloc(sizeof(char) * buf);
	if (!path)
		return (err(NULL, "malloc error", FAILURE));
	while (!getcwd(path, buf))
	{
		free(path);
		buf += 64;
		path = malloc(sizeof(char) * buf);
		if (!path)
			return (err(NULL, "malloc error", FAILURE));
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (SUCCESS);
}
