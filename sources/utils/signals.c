/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:45:57 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/08 09:58:53 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <term.h>

extern int	g_signal;

void	handle_signal(int signum)
{
	char	*prompt;

	(void)signum;
	g_signal = 0;
	prompt = get_prompt();
	if (GNL)
		ft_printf("\n%s", prompt);
	else
		ft_printf("\n");
	free(prompt);
	if (!GNL)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	handle_child_signal(int signum)
{
	g_signal = signum;
	full_exit(2);
}

void	handle_hd_signal(int signum)
{
	g_signal = signum;
	ft_printf("\n");
	full_exit(130);
}

void	update_signal(int signum)
{
	g_signal = signum;
}

void	update_signal_hd(int signum)
{
	g_signal = signum;
	get_ms()->last_exit = 131;
}
