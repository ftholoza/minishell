/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:33:55 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 14:32:13 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_cmd_type	last_op(t_dlist *lst)
{
	t_exec_cmd	*cmd;

	while (lst)
	{
		cmd = lst->data;
		if (cmd->left != piping)
			return (cmd->left);
		lst = lst->prev;
	}
	return (none);
}

void	update_exit(t_exec_cmd *cmd, int new_exit)
{
	if (cmd->left == none || cmd->left == piping || cmd->left == and)
		cmd->parent->exit_status = new_exit;
	else if (cmd->left == or)
	{
		if (cmd->parent->exit_status != 0)
			cmd->parent->exit_status = new_exit;
	}
}
