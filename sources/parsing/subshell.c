/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:05:19 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:50:30 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	browse_comp_cmds(t_dlist **lst, t_exec_cmd *parent,
	t_computed_cmd **data, enum e_cmd_type left)
{
	while (*lst)
	{
		*data = (*lst)->data;
		if ((*data)->type == open_p)
			create_subs_open_p(lst, parent, data, left);
		else if (*data && (*data)->type == close_p)
			break ;
		else if (*data && (*data)->type == cmd)
			save_cmd(lst, parent, data, left);
		if (*lst && ((*data)->type == and || (*data)->type == or
				|| (*data)->type == piping))
		{
			left = (*data)->type;
			*lst = (*lst)->next;
		}
	}
}

void	update_subs_right(t_dlist **lst, t_computed_cmd **data, t_exec_cmd *new)
{
	*data = (*lst)->next->data;
	if ((*data)->type == piping || (*data)->type == and
		|| (*data)->type == or)
		new->right = ((t_computed_cmd *)(*lst)->next->data)->type;
	else
		set_subshell_redir(new, data, lst);
}

void	*create_subs_open_p(t_dlist **lst, t_exec_cmd *parent,
	t_computed_cmd **data, enum e_cmd_type left)
{
	t_exec_cmd	*new;

	*lst = (*lst)->next;
	*data = (t_computed_cmd *)(*lst)->data;
	new = malloc(sizeof(t_exec_cmd));
	if (!new)
		return (err_null("minishell: malloc error"));
	init_subs(new, left, parent);
	left = none;
	browse_comp_cmds(lst, new, data, left);
	new->right = none;
	if ((*lst) && (*lst)->next)
		update_subs_right(lst, data, new);
	ft_dl_add_back(&parent->cmds, ft_dl_new(new));
	if (*lst)
		*lst = (*lst)->next;
	return (NULL);
}

void	*save_cmd(t_dlist **lst, t_exec_cmd *parent, t_computed_cmd	**data,
	enum e_cmd_type left)
{
	t_exec_cmd	*new;

	new = malloc(sizeof(t_exec_cmd));
	if (!new)
		return (err_null("minishell: malloc error"));
	ft_bzero(new, sizeof(t_exec_cmd));
	new->type = cmd;
	new->parent = parent;
	new->left = left;
	new->cmd = dup_comp_cmd(*data);
	*lst = (*lst)->next;
	new->right = none;
	if (*lst)
	{
		*data = (t_computed_cmd *)(*lst)->data;
		if ((*data)->type == piping || (*data)->type == and
			|| (*data)->type == or)
			new->right = (*data)->type;
	}
	else
		*data = NULL;
	ft_dl_add_back(&parent->cmds, ft_dl_new(new));
	return (NULL);
}

t_exec_cmd	*create_subshell(t_dlist *lst)
{
	t_computed_cmd	*data;
	t_exec_cmd		*subshell;
	t_dlist			**ptr;
	enum e_cmd_type	left;

	ptr = &lst;
	subshell = malloc(sizeof(t_exec_cmd));
	if (!subshell)
		return (err_null("minishell: malloc error"));
	ft_bzero(subshell, sizeof(t_exec_cmd));
	subshell->type = subs;
	subshell->left = none;
	subshell->right = none;
	subshell->in_fd = 0;
	subshell->out_fd = 1;
	left = none;
	browse_comp_cmds(ptr, subshell, &data, left);
	return (subshell);
}
