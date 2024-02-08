/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_specials.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:12:17 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:05:14 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_piping(t_cmds *cmds, char *str, int i, int len)
{
	t_split_cmd	*data;	

	while (str[i + len] && is_special(str[i + len]) == piping)
		len++;
	if (len == 1)
	{
		data = create_split_cmd(ft_substr(str, i, len), piping);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else if (len == 2)
	{
		data = create_split_cmd(ft_substr(str, i, len), or);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else
		return (err(NULL, "parse error near `|'", ERR_PARSING));
	return (i + len);
}

int	get_and(t_cmds *cmds, char *str, int i, int len)
{
	t_split_cmd	*data;	

	while (str[i + len] && is_special(str[i + len]) == and)
		len++;
	if (len == 1)
		return (err(NULL, "parse error near `&'", ERR_PARSING));
	else if (len == 2)
	{
		data = create_split_cmd(ft_substr(str, i, len), and);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else
		return (err(NULL, "parse error near `&'", ERR_PARSING));
	return (i + len);
}

int	get_open_p(t_cmds *cmds, char *str, int i)
{
	t_split_cmd	*data;	

	data = create_split_cmd(ft_substr(str, i, 1), open_p);
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	return (i + 1);
}

int	get_close_p(t_cmds *cmds, char *str, int i)
{
	t_split_cmd	*data;	

	data = create_split_cmd(ft_substr(str, i, 1), close_p);
	if (!data)
		return (err(NULL, "malloc error", ERR_MALLOC));
	ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	return (i + 1);
}
