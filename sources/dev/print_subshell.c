/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:12:20 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/02 17:51:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_type(enum e_cmd_type type)
{
	if (type == 23)
		return ("none");
	if (type == 22)
		return ("and");
	if (type == 21)
		return ("or");
	if (type == 20)
		return ("piping");
	return ("");
}

void	print_subs(t_exec_cmd *subshell)
{
	ft_printf("+------------------------------------------------------+\n");
	ft_printf("| SUBSHELL                                             |\n");
	ft_printf("+------------------------------------------------------+\n");
	ft_printf("| %-25s  %25s |\n", cmd_type(subshell->left),
		cmd_type(subshell->right));
	ft_printf("+------------------------------------------------------+\n");
}

void	print_end_subs(void)
{
	ft_printf("+------------------------------------------------------+\n");
	ft_printf("| END SUBSHELL                                         |\n");
	ft_printf("+------------------------------------------------------+\n");
}

void	print_cmd(t_exec_cmd *cmd)
{
	ft_printf("  | COMMAND                                          |\n");
	ft_printf("  | %-23s  %23s |\n", cmd_type(cmd->left), cmd_type(cmd->right));
	ft_printf("  | -> %-45s |\n", cmd->cmd->argv[0]);
	ft_printf("  |                                                  |\n");
}

void	print_subshell(t_exec_cmd *subshell)
{
	t_dlist		*lst;
	t_exec_cmd	*cmd;

	lst = subshell->cmds;
	print_subs(subshell);
	while (lst)
	{
		cmd = lst->data;
		if (cmd->type == subs)
			print_subshell(cmd);
		else
			print_cmd(cmd);
		lst = lst->next;
	}
	print_end_subs();
}
