/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_fade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:20:42 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/08 10:28:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*show_random_char_in(int i, int j)
{
	int		fd_rand;
	int		rand;
	int		r;
	char	*c;

	fd_rand = open("/dev/urandom", O_RDONLY);
	if (fd_rand < 0)
		return (err_null("minishell: unable to get random chars"));
	r = read(fd_rand, &rand, sizeof(int));
	if (r < 0)
		return (err_null("minishell: unable to read random chars"));
	close(fd_rand);
	c = get_random_char(1);
	if (ft_abs(rand % 100) < 15)
		ft_printf("\033[?25l\033[%d;%dH\033[%dm%s", i, j,
			ft_abs(rand % 4) + 33, c);
	free(c);
	return (NULL);
}

void	random_char_in(struct winsize w)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	while (++k <= 20)
	{
		i = 0;
		while (++i <= w.ws_row)
		{
			j = 0;
			while (++j <= w.ws_col)
				show_random_char_in(i, j);
		}
	}
}

void	show_title_out(struct winsize w, char **title, int i, int j)
{
	if (i < 9)
		ft_printf("\033[%d;%dH\033[35m%c", i, j,
			title[i - 2][j - (w.ws_col - 90) / 2]);
	else
		ft_printf("\033[%d;%dH\033[32m%c", i, j,
			title[i - 2][j - (w.ws_col - 90) / 2]);
}

void	*show_random_char_out(struct winsize w, char **title, int i, int j)
{
	int	fd_rand;
	int	rand;
	int	r;

	fd_rand = open("/dev/urandom", O_RDONLY);
	if (fd_rand < 0)
		return (err_null("minishell: unable to get random chars"));
	r = read(fd_rand, &rand, sizeof(int));
	if (r < 0)
		return (err_null("minishell: unable to read random chars"));
	close(fd_rand);
	if (ft_abs(rand % 100) < 16)
	{
		if (j < (w.ws_col - 90) / 2 || j > (w.ws_col - 90) / 2 + 90 - 1
			|| i == 1 || i > 10)
			ft_printf("\033[%d;%dH ", i, j);
		else
			show_title_out(w, title, i, j);
	}
	return (NULL);
}

void	random_char_out(struct winsize w, char **title)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	while (++k <= 30)
	{
		i = 0;
		while (++i <= w.ws_row)
		{
			j = 0;
			while (++j <= w.ws_col)
				show_random_char_out(w, title, i, j);
		}
	}
}
