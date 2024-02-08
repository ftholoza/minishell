/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:21:39 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/08 09:07:41 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_title(void)
{
	int		fd_title;
	char	**title;
	char	*line;
	int		nb_line;

	fd_title = open("./sources/title", O_RDONLY);
	if (fd_title < 0)
		return (err_null("minishell: unable to open file"));
	line = get_next_line(fd_title);
	title = malloc(sizeof(char *) * 10);
	if (!title)
		return (err_null("minishell: malloc error"));
	nb_line = -1;
	while (++nb_line < 9)
	{
		title[nb_line] = ft_strdup(line);
		free(line);
		line = get_next_line(fd_title);
	}
	close(fd_title);
	return (title);
}

void	clear_view(void)
{
	char	*intro;

	intro = ft_strdup("clear");
	if (parse_cmd(intro) == SUCCESS)
	{
		free(intro);
		get_cmds()->subshell = create_subshell(get_cmds()->computed);
		exec_shell(get_cmds()->subshell);
	}
	else
		free(intro);
	clear_cmds_lst();
}

void	show_prompt(struct winsize w, char **title)
{
	int		i;
	char	*prompt;

	i = -1;
	while (++i < 9)
	{
		if (i < 8)
			ft_printf("\033[%d;%dH\033[35m%s", i + 2, (w.ws_col - 90) / 2,
				title[i]);
		else
			ft_printf("\033[%d;%dH\033[32m%s", i + 2, (w.ws_col - 90) / 2,
				title[i]);
		free(title[i]);
	}
	ft_printf("\n\n\033[?25h\033[m");
	prompt = get_prompt();
	write(1, prompt, 18);
	i = 17;
	while (++i < (int)ft_strlen(prompt) - 1)
	{
		write(1, &prompt[i], 1);
	}
	ft_printf("\r                                                    \r");
	free(prompt);
}

void	intro(void)
{
	struct winsize	w;
	char			**title;

	ioctl(0, TIOCGWINSZ, &w);
	title = get_title();
	random_char_in(w);
	random_char_out(w, title);
	clear_view();
	show_prompt(w, title);
	free(title);
}
