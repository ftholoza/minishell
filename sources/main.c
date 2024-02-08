/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:03:52 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/01 16:51:59 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	minishell(void)
{
	while (1)
	{
		g_signal = 0;
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (GNL)
			ms_gnl();
		else
			ms_rl();
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_signal = 0;
	init_minishell(env);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (INTRO)
		intro();
	minishell();
	full_exit(0);
}
