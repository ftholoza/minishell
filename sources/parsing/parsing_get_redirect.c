/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:13:49 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:06:13 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_redirect(t_cmds *cmds, char *str, int i, int len)
{
	t_split_cmd	*data;	

	while (str[i + len] && is_special(str[i + len]) == input_redirect)
		len++;
	if (len == 1)
	{
		data = create_split_cmd(ft_substr(str, i, len), input_redirect);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else if (len == 2)
	{
		data = create_split_cmd(ft_substr(str, i, len), here_doc);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else
		return (err(NULL, "parse error near `<'", ERR_PARSING));
	return (i + len);
}

int	get_output_redirect(t_cmds *cmds, char *str, int i, int len)
{
	t_split_cmd	*data;	

	while (str[i + len] && is_special(str[i + len]) == output_redirect)
		len++;
	if (len == 1)
	{
		data = create_split_cmd(ft_substr(str, i, len), output_redirect);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else if (len == 2)
	{
		data = create_split_cmd(ft_substr(str, i, len), append_redirect);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&cmds->split_special, ft_dl_new(data));
	}
	else
		return (err(NULL, "parse error near `>'", ERR_PARSING));
	return (i + len);
}
