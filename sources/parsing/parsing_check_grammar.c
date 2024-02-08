/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_grammar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:20:38 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 17:05:24 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_prev_next_and_or_pipe(t_dlist *lst, char *msg)
{
	t_split_cmd	*data;

	if (lst->prev == NULL)
		return (err(NULL, msg, ERR_PARSING));
	data = lst->prev->data;
	if (data->type == and || data->type == or || data->type == piping
		|| data->type == append_redirect || data->type == output_redirect
		|| data->type == here_doc || data->type == input_redirect)
		return (err(NULL, msg, ERR_PARSING));
	if (lst->next == NULL)
		return (err(NULL, msg, ERR_PARSING));
	data = lst->next->data;
	if (data->type == and || data->type == or || data->type == piping)
		return (err(NULL, msg, ERR_PARSING));
	return (SUCCESS);
}

int	check_and_or_pipe(void)
{
	t_cmds		*cmds;
	t_dlist		*tmp;
	t_split_cmd	*data;

	cmds = get_cmds();
	tmp = cmds->connected;
	while (tmp)
	{
		data = tmp->data;
		if (data->type == and)
			if (check_prev_next_and_or_pipe(tmp,
					"parse error near `&&'") != SUCCESS)
				return (ERR_PARSING);
		if (data->type == or)
			if (check_prev_next_and_or_pipe(tmp,
					"parse error near `||'") != SUCCESS)
				return (ERR_PARSING);
		if (data->type == piping)
			if (check_prev_next_and_or_pipe(tmp,
					"parse error near `|'") != SUCCESS)
				return (ERR_PARSING);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_grammar(void)
{
	int	tmp;

	tmp = get_ms()->last_exit;
	get_ms()->last_exit = 2;
	if (check_parenthesis() != SUCCESS)
		return (ERR_PARSING);
	if (check_and_or_pipe() != SUCCESS)
		return (ERR_PARSING);
	if (check_redir() != SUCCESS)
		return (ERR_PARSING);
	get_ms()->last_exit = tmp;
	return (SUCCESS);
}
