/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:23:15 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:13:12 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exist(char *path)
{
	if (!path)
		return (0);
	return (access(path, F_OK) == 0);
}

int	check_type(char *path, enum e_type t)
{
	struct stat	file_stat;

	stat(path, &file_stat);
	if (t == file)
		return (S_ISREG(file_stat.st_mode));
	return (S_ISDIR(file_stat.st_mode));
}

int	check_perm(char *path, enum e_perm p)
{
	if (p == rwx)
		return (access(path, R_OK | W_OK | X_OK) == 0);
	else if (p == rw)
		return (access(path, R_OK | W_OK) == 0);
	else if (p == rx)
		return (access(path, R_OK | X_OK) == 0);
	else if (p == wx)
		return (access(path, W_OK | X_OK) == 0);
	else if (p == w)
		return (access(path, W_OK) == 0);
	else if (p == r)
		return (access(path, R_OK) == 0);
	return (access(path, X_OK) == 0);
}

int	check_write(char *path)
{
	if (check_exist(path) && check_type(path, dir))
		return (err(path, "Is a directory", ERR_FILE));
	if (check_exist(path) && !check_perm(path, w))
		return (err(path, "Permission denied", ERR_PERM));
	return (SUCCESS);
}

int	check_read(char *path)
{
	if (check_exist(path) && check_type(path, dir))
		return (err(path, "Is a directory", ERR_FILE));
	if (check_exist(path) && !check_perm(path, r))
		return (err(path, "Permission denied", ERR_PERM));
	return (SUCCESS);
}
