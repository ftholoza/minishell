/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:49:31 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/22 21:48:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_buffer(char *p_line, char *buf)
{
	char	*n_line;

	if (!p_line)
	{
		p_line = malloc(sizeof(char));
		if (!p_line)
			return (NULL);
		p_line[0] = 0;
	}
	if (!p_line[0] && !buf[0])
		return (clean_exit(p_line));
	n_line = join_str(p_line, buf);
	if (!n_line)
		return (clean_exit(p_line));
	free(p_line);
	return (n_line);
}

char	*read_fd(int fd, char *prev_line)
{
	char	*buffer;
	ssize_t	r;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	r = 1;
	while (r != 0 && get_endl_pos(prev_line) == -1)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[r] = 0;
		prev_line = add_buffer(prev_line, buffer);
	}
	free(buffer);
	return (prev_line);
}

char	*get_line(char *prev_line)
{
	int		endl_pos;
	char	*curr_line;
	size_t	i;

	endl_pos = get_endl_pos(prev_line);
	if (endl_pos == -1)
		endl_pos = gnl_strlen(prev_line) - 1;
	curr_line = malloc((endl_pos + 1 + 1) * sizeof(char));
	if (!curr_line)
		return (NULL);
	i = 0;
	while ((int)i < endl_pos + 1)
	{
		curr_line[i] = prev_line[i];
		i++;
	}
	curr_line[i] = 0;
	return (curr_line);
}

char	*save_line(char *p_line)
{
	int		endl_pos;
	int		p_line_len;
	char	*n_p_line;
	int		i;

	endl_pos = get_endl_pos(p_line);
	if (endl_pos == -1)
		return (clean_exit(p_line));
	p_line_len = ft_strlen(p_line);
	if (p_line_len - endl_pos == 1)
	{
		free(p_line);
		return (NULL);
	}
	n_p_line = malloc((p_line_len - endl_pos) * sizeof(char));
	if (!n_p_line)
		return (clean_exit(p_line));
	i = -1;
	while (endl_pos + 1 + ++i < p_line_len)
		n_p_line[i] = p_line[endl_pos + 1 + i];
	n_p_line[i] = 0;
	free(p_line);
	return (n_p_line);
}

char	*get_next_line(int fd)
{
	static char	*prev_line[4096];
	char		*curr_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	prev_line[fd] = read_fd(fd, prev_line[fd]);
	if (!prev_line[fd])
		return (NULL);
	if (!prev_line[fd][0])
	{
		free(prev_line[fd]);
		return (NULL);
	}
	curr_line = get_line(prev_line[fd]);
	prev_line[fd] = save_line(prev_line[fd]);
	return (curr_line);
}
