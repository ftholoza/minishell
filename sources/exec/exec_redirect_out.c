/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 00:30:46 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 20:33:04 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_output_redir(int *out_fd, t_dlist *wild_redir, t_split_cmd *data,
		t_split_cmd *w_data)
{
	if (ft_dl_size(wild_redir) > 1)
		return (err(data->str, "ambiguous redirect", ERR_FILE));
	if (ft_dl_size(wild_redir) == 1)
	{
		*out_fd = -1;
		if (check_write(w_data->str) != SUCCESS)
			return (ERR_FILE);
		*out_fd = open(w_data->str, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*out_fd < 0)
			return (err(((t_split_cmd *)wild_redir->data)->str,
					"No such file or directory", ERR_OPEN));
	}
	else
	{
		*out_fd = -1;
		if (check_write(data->str) != SUCCESS)
			return (ERR_FILE);
		*out_fd = open(data->str, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*out_fd < 0)
			return (err(data->str, "No such file or directory", ERR_OPEN));
	}
	return (SUCCESS);
}

int	proc_output_redir(int *out_fd, t_split_cmd *data)
{
	t_dlist	*lst;
	t_dlist	*wild_redir;
	int		quote;
	int		return_val;

	lst = data->pre_expand;
	free(data->str);
	data->str = ft_strdup("");
	expand_redir(&quote, lst, data);
	wild_redir = wildcard_redir(data, &quote);
	return_val = do_output_redir(out_fd, wild_redir, data, wild_redir->data);
	ft_dl_clear(&wild_redir, &free_split_cmd);
	return (return_val);
}

int	do_append_redir(int *out_fd, t_dlist *wild_redir, t_split_cmd *data,
		t_split_cmd *w_data)
{
	if (ft_dl_size(wild_redir) > 1)
		return (err(data->str, "ambiguous redirect", ERR_FILE));
	if (ft_dl_size(wild_redir) == 1)
	{
		*out_fd = -1;
		if (check_write(w_data->str) != SUCCESS)
			return (ERR_FILE);
		*out_fd = open(w_data->str, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*out_fd < 0)
			return (err(((t_split_cmd *)wild_redir->data)->str,
					"No such file or directory", ERR_OPEN));
	}
	else
	{
		*out_fd = -1;
		if (check_write(data->str) != SUCCESS)
			return (ERR_FILE);
		*out_fd = open(data->str, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (*out_fd < 0)
			return (err(data->str, "No such file or directory", ERR_OPEN));
	}
	return (SUCCESS);
}

int	proc_append_redir(int *out_fd, t_split_cmd *data)
{
	t_dlist	*lst;
	t_dlist	*wild_redir;
	int		quote;
	int		return_val;

	lst = data->pre_expand;
	free(data->str);
	data->str = ft_strdup("");
	expand_redir(&quote, lst, data);
	wild_redir = wildcard_redir(data, &quote);
	return_val = do_append_redir(out_fd, wild_redir, data, wild_redir->data);
	ft_dl_clear(&wild_redir, &free_split_cmd);
	return (return_val);
}

int	browse_redir_lst(t_split_cmd *data, int *out_fd, t_dlist *lst)
{
	if (data->type == output_redirect)
	{
		if (proc_output_redir(out_fd, data) != SUCCESS)
			return (ERR_FILE);
	}
	else
	{
		if (proc_append_redir(out_fd, data) != SUCCESS)
			return (ERR_FILE);
	}
	if (next_out(lst->next))
		close(*out_fd);
	return (SUCCESS);
}
