/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:18:07 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 17:11:18 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_prev_next_redir(t_dlist *lst, char *msg)
{
	t_split_cmd	*data;

	if (lst->next == NULL)
		return (err(NULL, msg, ERR_PARSING));
	data = lst->next->data;
	if (data->type == and || data->type == or || data->type == piping
		|| data->type == append_redirect || data->type == output_redirect
		|| data->type == here_doc || data->type == input_redirect)
		return (err(NULL, msg, ERR_PARSING));
	if (lst->prev == NULL)
		return (SUCCESS);
	data = lst->prev->data;
	if (data->type == append_redirect || data->type == output_redirect
		|| data->type == here_doc || data->type == input_redirect)
		return (err(NULL, msg, ERR_PARSING));
	return (SUCCESS);
}

int	check_output_redir(t_dlist *lst)
{
	t_split_cmd	*data;

	data = lst->data;
	if (data->type == output_redirect)
		if (check_prev_next_redir(lst, "parse error near `>'") != SUCCESS)
			return (ERR_PARSING);
	if (data->type == append_redirect)
		if (check_prev_next_redir(lst, "parse error near `>>'") != SUCCESS)
			return (ERR_PARSING);
	return (SUCCESS);
}

int	check_input_redir(t_dlist *lst)
{
	t_split_cmd	*data;

	data = lst->data;
	if (data->type == input_redirect)
		if (check_prev_next_redir(lst, "parse error near `<'") != SUCCESS)
			return (ERR_PARSING);
	if (data->type == here_doc)
		if (check_prev_next_redir(lst, "parse error near `<<'") != SUCCESS)
			return (ERR_PARSING);
	return (SUCCESS);
}

int	check_redir(void)
{
	t_cmds		*cmds;
	t_dlist		*tmp;
	t_split_cmd	*data;

	cmds = get_cmds();
	tmp = cmds->connected;
	while (tmp)
	{
		data = tmp->data;
		if (data->type == output_redirect || data->type == append_redirect)
			if (check_output_redir(tmp) != SUCCESS)
				return (ERR_PARSING);
		if (data->type == input_redirect || data->type == here_doc)
			if (check_input_redir(tmp) != SUCCESS)
				return (ERR_PARSING);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
