/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:35:32 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 21:54:49 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_hd(t_split_cmd *cmd)
{
	int		fd;
	char	*line;
	char	*content;

	if (check_read(cmd->str) != SUCCESS)
		return (NULL);
	fd = open(cmd->str, O_RDONLY);
	if (fd < 0)
		return (err_null("minishell: unable to read heredoc"));
	content = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		content = ft_str_append(content, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

int	expand_hd(t_split_cmd *cmd)
{
	int			fd;
	char		*content;
	t_split_cmd	*tmp_cmd;

	content = read_hd(cmd);
	tmp_cmd = create_split_cmd(ft_strdup(content), 0);
	free(content);
	if (!cmd)
		return (err(NULL, "malloc error", ERR_MALLOC));
	expand(tmp_cmd);
	content = ft_strdup(tmp_cmd->str);
	free_split_cmd(tmp_cmd);
	fd = open(cmd->str, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	write(fd, content, ft_strlen(content));
	free(content);
	return (SUCCESS);
}

int	hd_rl(t_split_cmd *cmd, int fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (!line)
		return (hd_err(cmd->str));
	while (ft_strncmp(line, cmd->str, ft_strlen(cmd->str) + 1) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
		if (!line)
			return (hd_err(cmd->str));
	}
	if (line)
		free(line);
	return (SUCCESS);
}

int	hd_gnl(t_split_cmd *cmd, int fd)
{
	char	*line;

	ft_printf("heredoc> ");
	line = get_next_line(0);
	if (!line)
		return (hd_err(cmd->str));
	if (ft_strlen(line) > 0)
		line[ft_strlen(line) - 1] = 0;
	while (ft_strncmp(line, cmd->str, ft_strlen(cmd->str) + 1) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!line)
			return (hd_err(cmd->str));
		if (ft_strlen(line) > 0)
			line[ft_strlen(line) - 1] = 0;
	}
	free(line);
	return (SUCCESS);
}

void	heredoc(t_split_cmd *cmd)
{
	char	*rand;
	char	*path;
	int		fd;

	rand = get_random_char(64);
	path = add_path("/tmp", rand);
	free(rand);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	save_hd(cmd, fd);
	close(fd);
	free(cmd->str);
	cmd->str = path;
}
