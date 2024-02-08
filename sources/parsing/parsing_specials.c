/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_specials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:06:06 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:59:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special(int special, char *str, int i, int len)
{
	t_cmds	*cmds;

	cmds = get_cmds();
	if (special == input_redirect)
		return (get_input_redirect(cmds, str, i, len));
	else if (special == output_redirect)
		return (get_output_redirect(cmds, str, i, len));
	else if (special == piping)
		return (get_piping(cmds, str, i, len));
	else if (special == and)
		return (get_and(cmds, str, i, len));
	else if (special == open_p)
		return (get_open_p(cmds, str, i));
	else if (special == close_p)
		return (get_close_p(cmds, str, i));
	return (i + len);
}

int	get_special_parts(char *str, int i)
{
	int				len;
	enum e_cmd_type	special;
	t_split_cmd		*data;	

	len = 0;
	special = is_special(str[i]);
	if (special > 0)
		return (handle_special(special, str, i, len));
	else
	{
		while (str[i + len] && is_special(str[i + len]) == 0)
			len++;
		data = create_split_cmd(ft_substr(str, i, len), no_quote);
		if (!data)
			return (err(NULL, "malloc error", ERR_MALLOC));
		ft_dl_add_back(&get_cmds()->split_special, ft_dl_new(data));
		return (i + len);
	}
}

int	split_special_cmd(char *str, int connected)
{
	int		i;
	int		len;
	t_cmds	*cmds;

	cmds = get_cmds();
	i = 0;
	len = ft_strlen(str);
	while (i >= 0 && i < len)
		i = get_special_parts(str, i);
	if (i < 0)
	{
		ft_dl_clear(&cmds->split_special, &free_split_cmd);
		return (i);
	}
	if (((t_split_cmd *)ft_dl_last(cmds->split_special)->data)->type
		<= double_quotes)
		((t_split_cmd *)ft_dl_last(cmds->split_special)->data)->connected
			= connected;
	return (SUCCESS);
}

int	parse_cmd_special(void)
{
	t_dlist		*lst;
	t_split_cmd	*data;

	lst = get_cmds()->split_space;
	while (lst)
	{
		data = lst->data;
		if (data->type == no_quote)
		{
			if (split_special_cmd(data->str, data->connected) != SUCCESS)
				return (ERR_PARSING);
		}
		else if (data->type == single_quote)
			ft_dl_add_back(&get_cmds()->split_special,
				ft_dl_new(dup_split_cmd(data)));
		else if (data->type == double_quotes)
			ft_dl_add_back(&get_cmds()->split_special,
				ft_dl_new(dup_split_cmd(data)));
		lst = lst->next;
	}
	return (SUCCESS);
}
