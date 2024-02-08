/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:40:22 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:15:20 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hd_err(char *str)
{
	ft_putstr_fd("\nminishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	return (FAILURE);
}

void	*err_null(char *str)
{
	ft_putendl_fd(str, 2);
	return (NULL);
}

int	err(char *file, char *str, int return_val)
{
	ft_putstr_fd("minishell: ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
	return (return_val);
}
