/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:01:46 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:01:05 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_no_quote_cmd(char *str, int i, int len)
{
	t_cmds		*cmds;
	t_split_cmd	*data;

	cmds = get_cmds();
	while (str[i + len] && get_cmd_quote(str[i + len]) == no_quote)
		len++;
	data = malloc(sizeof(t_split_cmd));
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	data->str = ft_substr(str, i, len);
	data->type = no_quote;
	data->connected = !ft_isspace(str[i + len - 1]);
	data->pre_expand = NULL;
	ft_dl_add_back(&cmds->split_quote, ft_dl_new(data));
	return (i + len);
}

int	get_single_quote_cmd(char *str, int i, int len)
{
	t_cmds		*cmds;
	t_split_cmd	*data;

	cmds = get_cmds();
	i++;
	while (str[i + len] && get_cmd_quote(str[i + len]) != single_quote)
		len++;
	if (str[i + len] != '\'')
		return (err(NULL, "parse error near `''", ERR_QUOTE));
	data = malloc(sizeof(t_split_cmd));
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	data->str = ft_substr(str, i, len);
	data->type = single_quote;
	data->connected = !ft_isspace(str[i + len + 1]);
	data->pre_expand = NULL;
	ft_dl_add_back(&cmds->split_quote, ft_dl_new(data));
	len++;
	return (i + len);
}

int	get_double_quotes_cmd(char *str, int i, int len)
{
	t_cmds		*cmds;
	t_split_cmd	*data;

	cmds = get_cmds();
	i++;
	while (str[i + len] && get_cmd_quote(str[i + len]) != double_quotes)
		len++;
	if (str[i + len] != '"')
		return (err(NULL, "parse error near `\"'", ERR_QUOTE));
	data = malloc(sizeof(t_split_cmd));
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	data->str = ft_substr(str, i, len);
	data->type = double_quotes;
	data->connected = !ft_isspace(str[i + len + 1]);
	data->pre_expand = NULL;
	ft_dl_add_back(&cmds->split_quote, ft_dl_new(data));
	len++;
	return (i + len);
}
