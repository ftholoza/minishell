/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:55:03 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:57:09 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_no_quote_cmd(t_split_cmd *data)
{
	char		**splitted;
	int			i;
	t_cmds		*cmds;
	t_split_cmd	*new;

	cmds = get_cmds();
	splitted = ft_space_split(data->str);
	i = -1;
	while (splitted[++i])
	{
		new = malloc(sizeof(t_split_cmd));
		if (!new)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_bzero(new, sizeof(t_split_cmd));
		new->str = ft_strdup(splitted[i]);
		new->type = no_quote;
		new->pre_expand = NULL;
		if (!splitted[i + 1])
			new->connected = data->connected;
		ft_dl_add_back(&cmds->split_space, ft_dl_new(new));
		free(splitted[i]);
	}
	free(splitted);
	return (SUCCESS);
}

int	get_cmd_part(char *str, int i)
{
	int		type;
	int		len;

	len = 0;
	type = get_cmd_quote(str[i]);
	if (type == no_quote)
		return (get_no_quote_cmd(str, i, len));
	else if (type == single_quote)
		return (get_single_quote_cmd(str, i, len));
	else
		return (get_double_quotes_cmd(str, i, len));
	return (i);
}
