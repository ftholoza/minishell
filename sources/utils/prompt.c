/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:10:30 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 15:09:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_folder(void)
{
	char	*home;
	char	*path;
	char	*ptr;
	char	*folder;

	path = pwd();
	if (!path)
		return (ft_strdup("minishell"));
	home = ft_getenv("HOME");
	if (home && home[0] != 0
		&& ft_strncmp(path, home, ft_strlen(path) + 1) == 0)
		folder = ft_strdup("~");
	else
	{
		ptr = ft_strrchr(path, '/');
		ptr++;
		folder = ft_strdup(ptr);
	}
	free(path);
	if (folder && folder[0] == 0)
		folder = ft_str_append(folder, "/");
	return (folder);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*folder;

	if (!get_ms()->last_exit)
		prompt = ft_strdup("\001\033[1;32m\002➜  \001\033[1;36m\002");
	else
		prompt = ft_strdup("\001\033[1;31m\002➜  \001\033[1;36m\002");
	folder = get_folder();
	prompt = ft_str_append(prompt, folder);
	free(folder);
	prompt = ft_str_append(prompt, " \001\033[0m\002");
	return (prompt);
}

void	ms_rl(void)
{
	char	*prompt;
	char	*line;
	char	*cleanstr;

	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	if (!line)
		full_exit(SUCCESS);
	cleanstr = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (ft_strlen(cleanstr) > 0)
		add_history(cleanstr);
	if (parse_cmd(cleanstr) == SUCCESS)
	{
		free(cleanstr);
		get_cmds()->subshell = create_subshell(get_cmds()->computed);
		exec_shell(get_cmds()->subshell);
	}
	else
		free(cleanstr);
	unlink_all(get_cmds()->subshell);
	clear_cmds_lst();
}

void	ms_gnl(void)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt();
	ft_printf("%s", prompt);
	free(prompt);
	line = get_next_line(0);
	if (!line)
	{
		ft_printf("\n");
		full_exit(SUCCESS);
	}
	if (ft_strlen(line) > 0)
		line[ft_strlen(line) - 1] = 0;
	if (parse_cmd(line) == SUCCESS)
	{
		free(line);
		get_cmds()->subshell = create_subshell(get_cmds()->computed);
		exec_shell(get_cmds()->subshell);
	}
	else
		free(line);
	unlink_all(get_cmds()->subshell);
	clear_cmds_lst();
}
