/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_parenthesis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:16:07 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 17:05:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_p(t_dlist *lst, int *status_p)
{
	t_split_cmd	*data;

	(*status_p)++;
	if (lst->next == NULL)
		return (err(NULL, "parse error near `('", ERR_PARSING));
	data = lst->next->data;
	if (data->type == piping || data->type == and || data->type == or
		|| data->type == close_p)
		return (err(NULL, "parse error near `('", ERR_PARSING));
	if (lst->prev == NULL)
		return (SUCCESS);
	data = lst->prev->data;
	if (data->type == piping || data->type == and || data->type == or
		|| data->type == open_p)
		return (SUCCESS);
	return (err(NULL, "parse error near `('", ERR_PARSING));
}

int	check_close_p(t_dlist *lst, int *status_p)
{
	t_split_cmd	*data;

	(*status_p)--;
	if (lst->prev == NULL)
		return (err(NULL, "parse error near `)'", ERR_PARSING));
	data = lst->prev->data;
	if (data->type == piping || data->type == and || data->type == or
		|| data->type == open_p)
		return (err(NULL, "parse error near `)'", ERR_PARSING));
	if (lst->next == NULL)
		return (SUCCESS);
	data = lst->next->data;
	if (data->type == piping || data->type == and || data->type == or
		|| data->type == close_p
		|| data->type == input_redirect || data->type == here_doc
		|| data->type == output_redirect || data->type == append_redirect)
		return (SUCCESS);
	return (err(NULL, "parse error near `)'", ERR_PARSING));
}

int	check_parenthesis(void)
{
	t_cmds		*cmds;
	t_dlist		*tmp;
	t_split_cmd	*data;
	int			status_p;

	cmds = get_cmds();
	tmp = cmds->connected;
	status_p = 0;
	while (tmp)
	{
		data = tmp->data;
		if (data->type == open_p)
			if (check_open_p(tmp, &status_p) != SUCCESS)
				return (ERR_PARSING);
		if (data->type == close_p)
			if (check_close_p(tmp, &status_p) != SUCCESS)
				return (ERR_PARSING);
		tmp = tmp->next;
		if (status_p < 0)
			return (err(NULL, "parse error near `)'", ERR_PARSING));
	}
	if (status_p != 0)
		return (err(NULL, "parse error near `('", ERR_PARSING));
	return (SUCCESS);
}
