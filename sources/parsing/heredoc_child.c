/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:59:17 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 10:57:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

int	save_hd(t_split_cmd *cmd, int fd)
{
	pid_t	pid;

	if (g_signal != 0)
		return (FAILURE);
	signal(SIGINT, &update_signal_hd);
	pid = fork();
	if (pid < 0)
		return (err(NULL, "unable to fork", ERR_FORK));
	if (!pid)
	{
		signal(SIGINT, &handle_hd_signal);
		signal(SIGQUIT, SIG_IGN);
		if (GNL)
			hd_gnl(cmd, fd);
		else
			hd_rl(cmd, fd);
		exit(SUCCESS);
	}
	waitpid(pid, NULL, 0);
	signal(SIGINT, &handle_signal);
	return (SUCCESS);
}
