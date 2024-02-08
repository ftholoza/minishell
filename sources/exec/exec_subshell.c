/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:59:04 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 11:59:33 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	run_cmd(t_exec_cmd *cmd, t_dlist *lst)
{
	if (g_signal == SIGINT)
		return ;
	if ((last_op(lst) == and && cmd->parent->exit_status == 0)
		|| (last_op(lst) == or && cmd->parent->exit_status != 0)
		|| last_op(lst) == none)
	{
		if (cmd->type != subs)
		{
			expand_args(cmd);
			if (is_builtin(cmd))
				exec_builtin(cmd, lst);
		}
		if (!is_builtin(cmd))
			execute_cmd(cmd, lst);
	}
}

int	process_subs_io_redir(t_split_cmd *data, int *in_fd, int *out_fd,
		t_dlist *lst)
{
	if (data->type <= here_doc_quote)
	{
		if (data->type == here_doc)
			expand_hd(data);
		if (proc_in_redir(in_fd, data) != SUCCESS)
			return (ERR_OPEN);
		if (next_in(lst->next))
			close(*in_fd);
	}
	else
	{
		if (browse_redir_lst(data, out_fd, lst) != SUCCESS)
			return (ERR_OPEN);
		if (next_out(lst->next))
			close(*out_fd);
	}
	return (SUCCESS);
}

int	process_subs_redir(t_exec_cmd *subshell)
{
	t_dlist		*lst;
	t_split_cmd	*data;
	int			in_fd;
	int			out_fd;

	out_fd = 0;
	lst = subshell->redir;
	while (lst)
	{
		data = lst->data;
		if (process_subs_io_redir(data, &in_fd, &out_fd, lst) != SUCCESS)
			return (ERR_OPEN);
		lst = lst->next;
	}
	if (next_in(subshell->redir))
		subshell->in_fd = in_fd;
	if (next_out(subshell->redir))
		subshell->out_fd = out_fd;
	return (SUCCESS);
}

void	exec_shell(t_exec_cmd *subshell)
{
	t_dlist	*cmds;

	ft_bzero(get_ms()->pids, sizeof(pid_t) * 1024);
	cmds = subshell->cmds;
	if (subshell->redir)
		if (process_subs_redir(subshell) != SUCCESS)
			return ;
	while (cmds)
	{
		run_cmd(cmds->data, cmds);
		cmds = cmds->next;
	}
	if (!subshell->parent)
		get_ms()->last_exit = subshell->exit_status;
}
