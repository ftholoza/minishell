/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:20:04 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 11:58:03 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_custom_expand(t_split_cmd *pre_ex)
{
	t_ms	*ms;
	char	*exit;
	char	*tmp;

	ms = get_ms();
	tmp = ft_strdup(pre_ex->str);
	free(pre_ex->str);
	exit = ft_itoa(ms->last_exit);
	if (tmp[1] == '0')
		pre_ex->str = ft_strdup("minishell");
	else if (tmp[1] == '?')
		pre_ex->str = ft_strdup(exit);
	else if (tmp[1] == '$')
		pre_ex->str = ft_strdup("$$");
	else
		pre_ex->str = ft_strdup("$");
	free(exit);
	free(tmp);
}

void	ft_expander(t_split_cmd *pre_ex)
{
	char	*value;
	char	*var;
	char	*tmp;

	if (pre_ex->str[0] != '$' || pre_ex->type == single_quote)
		return ;
	if (is_custom_expand(pre_ex->str[1]))
		ft_custom_expand(pre_ex);
	else
	{
		tmp = ft_strdup(pre_ex->str);
		free(pre_ex->str);
		var = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		value = ft_getenv(var);
		free(var);
		if (value)
			pre_ex->str = ft_strdup(value);
		else
			pre_ex->str = ft_strdup("");
		free(tmp);
	}
}

void	browse_pre_ex(t_split_cmd *data, t_exec_cmd *cmd, int *quote, int i)
{
	if (data)
	{
		if (data->type != no_quote && ft_strchr(data->str, '*') != NULL)
			*quote = 1;
		ft_expander(data);
		cmd->cmd->argv[i] = ft_str_append(cmd->cmd->argv[i], data->str);
	}
}

void	expand_arg(t_exec_cmd *cmd, t_dlist *pre_ex, int i)
{
	int			one_var;
	int			quote;
	t_split_cmd	*data;

	quote = 0;
	one_var = -1;
	if (ft_dl_size(pre_ex) == 1)
		one_var = 0;
	while (pre_ex)
	{
		data = pre_ex->data;
		if (data->str[0] == '$' && data->type != single_quote
			&& one_var == 0)
			one_var = 1;
		browse_pre_ex(data, cmd, &quote, i);
		pre_ex = pre_ex->next;
	}
	if (cmd->cmd->argv[i][0] == 0 && one_var == 1)
	{
		free(cmd->cmd->argv[i]);
		cmd->cmd->argv[i] = NULL;
	}
	else
		check_wildcards(cmd, quote, i);
}

void	expand_args(t_exec_cmd *cmd)
{
	t_dlist		**pre_ex_array;
	t_dlist		*pre_ex;
	int			i;

	pre_ex_array = cmd->cmd->pre_expand;
	i = -1;
	while (pre_ex_array[++i])
	{
		cmd->cmd->argv[i] = ft_strdup("");
		pre_ex = pre_ex_array[i];
		expand_arg(cmd, pre_ex, i);
	}
	wild_to_argv(cmd);
}
