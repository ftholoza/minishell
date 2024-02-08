/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:01:39 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:57:51 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_subshell_redir(t_exec_cmd *new, t_computed_cmd **data,
	t_dlist **lst)
{
	new->redir = (*data)->redir;
	(*data)->redir = NULL;
	if ((*lst)->next->next)
	{
		*data = (*lst)->next->next->data;
		if ((*data)->type == piping || (*data)->type == and
			|| (*data)->type == or)
			new->right = (*data)->type;
	}
	*lst = (*lst)->next;
}

void	init_subs(t_exec_cmd *new, enum e_cmd_type left, t_exec_cmd *parent)
{
	ft_bzero(new, sizeof(t_exec_cmd));
	new->type = subs;
	new->left = left;
	new->parent = parent;
}
