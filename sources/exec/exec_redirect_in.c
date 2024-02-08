/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:16:09 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 21:55:58 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_in_redir(int *in_fd, t_dlist *wild_redir, t_split_cmd *data)
{
	if (ft_dl_size(wild_redir) > 1)
		return (err(data->str, "ambiguous redirect", ERR_FILE));
	if (ft_dl_size(wild_redir) == 1)
	{
		*in_fd = -1;
		if (check_read(((t_split_cmd *)wild_redir->data)->str) != SUCCESS)
			return (ERR_FILE);
		*in_fd = open(((t_split_cmd *)wild_redir->data)->str, O_RDONLY);
		if (*in_fd < 0)
			return (err(((t_split_cmd *)wild_redir->data)->str,
					"No such file or directory", ERR_OPEN));
	}
	else
	{
		*in_fd = -1;
		if (check_read(data->str) != SUCCESS)
			return (ERR_FILE);
		*in_fd = open(data->str, O_RDONLY);
		if (*in_fd < 0)
			return (err(data->str, "No such file or directory", ERR_OPEN));
	}
	return (SUCCESS);
}

int	proc_in_redir(int *in_fd, t_split_cmd *data)
{
	t_dlist		*lst;
	t_dlist		*wild_redir;
	int			quote;
	int			return_val;

	if (data->type == here_doc || data->type == here_doc_quote)
	{
		*in_fd = -1;
		if (check_read(data->str) != SUCCESS)
			return (ERR_FILE);
		*in_fd = open(data->str, O_RDONLY);
		if (*in_fd < 0)
			return (err(data->str, "No such file or directory", ERR_OPEN));
		return (SUCCESS);
	}
	lst = data->pre_expand;
	free(data->str);
	data->str = ft_strdup("");
	expand_redir(&quote, lst, data);
	wild_redir = wildcard_redir(data, &quote);
	return_val = do_in_redir(in_fd, wild_redir, data);
	ft_dl_clear(&wild_redir, &free_split_cmd);
	return (return_val);
}

int	process_io_redir(t_split_cmd *data, int *in_fd, int *out_fd, t_dlist *lst)
{
	if (data->type <= here_doc_quote)
	{
		if (data->type == here_doc)
			expand_hd(data);
		if (proc_in_redir(in_fd, data) != SUCCESS)
			return (ERR_FILE);
		if (next_in(lst->next))
			close(*in_fd);
	}
	else
	{
		if (browse_redir_lst(data, out_fd, lst) != SUCCESS)
			return (ERR_FILE);
		if (next_out(lst->next))
			close(*out_fd);
	}
	return (SUCCESS);
}

int	process_redir(t_exec_cmd *cmd)
{
	t_dlist		*lst;
	t_split_cmd	*data;
	int			in_fd;
	int			out_fd;

	out_fd = cmd->out_fd;
	lst = cmd->cmd->redir;
	while (lst)
	{
		data = lst->data;
		if (process_io_redir(data, &in_fd, &out_fd, lst) != SUCCESS)
			return (ERR_FILE);
		lst = lst->next;
	}
	if (next_in(cmd->cmd->redir))
	{
		dup2(in_fd, cmd->in_fd);
		close(in_fd);
	}
	if (next_out(cmd->cmd->redir))
	{
		dup2(out_fd, cmd->out_fd);
		close(out_fd);
	}
	return (SUCCESS);
}
