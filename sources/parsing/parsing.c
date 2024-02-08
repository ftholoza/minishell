/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:33:18 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:21:39 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_cmd_type	get_cmd_quote(char c)
{
	if (c == '\'')
		return (single_quote);
	else if (c == '"')
		return (double_quotes);
	return (no_quote);
}

enum e_cmd_type	is_special(char c)
{
	if (c == '<')
		return (input_redirect);
	if (c == '>')
		return (output_redirect);
	if (c == '|')
		return (piping);
	if (c == '&')
		return (and);
	if (c == '(')
		return (open_p);
	if (c == ')')
		return (close_p);
	return (0);
}

int	split_no_quote(t_dlist *lst)
{
	t_split_cmd	*data;

	while (lst)
	{
		data = lst->data;
		if (data->type == no_quote)
		{
			if (split_no_quote_cmd(data) != SUCCESS)
				return (ERR_PARSING);
		}
		else
			ft_dl_add_back(&get_cmds()->split_space,
				ft_dl_new(dup_split_cmd(data)));
		lst = lst->next;
	}
	return (SUCCESS);
}

int	parse_clean_line(char *cleanstr)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(cleanstr);
	while (i >= 0 && i < len)
		i = get_cmd_part(cleanstr, i);
	if (i < 0)
		return (ft_free(ERR_PARSING, "v", cleanstr));
	free(cleanstr);
	((t_split_cmd *)ft_dl_last(get_cmds()->split_quote)->data)->connected = 0;
	if (split_no_quote(get_cmds()->split_quote) != SUCCESS)
		return (ERR_PARSING);
	if (parse_cmd_special() != SUCCESS)
		return (ERR_PARSING);
	update_connected(get_cmds()->split_special);
	if (parse_cmd_var(get_cmds()->split_special))
		return (ERR_PARSING);
	connect_args(get_cmds()->split_var);
	if (check_grammar() != SUCCESS)
		return (ERR_PARSING);
	return (SUCCESS);
}

int	parse_cmd(char *str)
{
	char	*cleanstr;
	int		tmp;

	cleanstr = ft_strtrim(str, " \f\n\r\t\v");
	if (!cleanstr)
		return (err(NULL, "malloc error", ERR_MALLOC));
	if (ft_strlen(cleanstr) == 0)
		return (ft_free(ERR_EMPTY_CMD, "v", cleanstr));
	tmp = get_ms()->last_exit;
	get_ms()->last_exit = 2;
	if (parse_clean_line(cleanstr) != SUCCESS)
		return (ERR_PARSING);
	get_ms()->last_exit = tmp;
	return (compute_cmds());
}
