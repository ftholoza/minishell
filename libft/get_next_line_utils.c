/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:31:41 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/13 14:24:07 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*join_str(char *p_line, char *buf)
{
	char	*n_line;
	int		p_len;
	int		b_len;
	int		i;

	p_len = ft_strlen(p_line);
	b_len = ft_strlen(buf);
	n_line = malloc((p_len + b_len + 1) * sizeof(char));
	if (!n_line)
		return (NULL);
	i = -1;
	while (++i < p_len)
		n_line[i] = p_line[i];
	i--;
	while (++i < b_len + p_len)
		n_line[i] = buf[i - p_len];
	n_line[i] = 0;
	return (n_line);
}

void	*clean_exit(char *p_line)
{
	free(p_line);
	return (NULL);
}

int	gnl_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_endl_pos(char *prev_line)
{
	int		endl_pos;

	if (!prev_line)
		return (-1);
	endl_pos = 0;
	while (prev_line[endl_pos] && prev_line[endl_pos] != '\n')
		endl_pos++;
	if (prev_line[endl_pos] == '\n')
		return (endl_pos);
	return (-1);
}
