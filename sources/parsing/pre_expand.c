/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:12:24 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 16:08:14 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pre_expand	*create_pre_expand(char *str, enum e_cmd_type type)
{
	t_pre_expand	*data;

	data = malloc(sizeof(t_pre_expand));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_pre_expand));
	data->str = str;
	data->type = type;
	return (data);
}

void	pre_expand_custom(char c, int *i, t_split_cmd *data, t_dlist *lst)
{
	(void)lst;
	if (c == '0' || c == '?' || c == '$')
		(*i)++;
	if (c == '0')
		ft_dl_add_back(&get_cmds()->split_var,
			ft_dl_new(create_split_cmd(ft_strdup("$0"), data->type)));
	else if (c == '?')
		ft_dl_add_back(&get_cmds()->split_var,
			ft_dl_new(create_split_cmd(ft_strdup("$?"), data->type)));
	else if (c == '$')
		ft_dl_add_back(&get_cmds()->split_var,
			ft_dl_new(create_split_cmd(ft_strdup("$$"), data->type)));
	else if (data->type != no_quote || !data->connected
		|| (ft_strlen(data->str) > 1 && !is_var_char(data->str[1])))
		ft_dl_add_back(&get_cmds()->split_var,
			ft_dl_new(create_split_cmd(ft_strdup("$"), data->type)));
	else if (data->type == no_quote && data->connected)
		return ;
	if (data->str[*i])
		((t_split_cmd *)ft_dl_last(get_cmds()->split_var)->data)->connected = 1;
	else
		((t_split_cmd *)ft_dl_last(get_cmds()->split_var)->data)->connected
			= data->connected;
}

void	pre_expander(t_split_cmd *data, int *i, t_dlist *lst)
{
	int			start;
	t_split_cmd	*new;

	(*i)++;
	start = *i;
	if (is_custom_expand(data->str[*i]))
		pre_expand_custom(data->str[*i], i, data, lst);
	else
	{
		while (data->str[*i] && is_var_char(data->str[*i]))
			(*i)++;
		new = create_split_cmd(ft_substr(data->str, start - 1, *i - start + 1),
				data->type);
		if (data->str[*i])
			new->connected = 1;
		else
			new->connected = data->connected;
		ft_dl_add_back(&get_cmds()->split_var, ft_dl_new(new));
	}
}

void	pre_expand(t_split_cmd *data, t_dlist *lst)
{
	int			i;
	int			start;
	t_split_cmd	*new;

	i = 0;
	if (data->str[0] == 0)
		ft_dl_add_back(&get_cmds()->split_var, ft_dl_new(dup_split_cmd(data)));
	while (data->str[i])
	{
		start = i;
		while (data->str[i] && data->str[i] != '$')
			i++;
		if (i != start)
		{
			new = create_split_cmd(ft_substr(data->str, start, i - start),
					data->type);
			if (data->str[i])
				new->connected = 1;
			else
				new->connected = data->connected;
			ft_dl_add_back(&get_cmds()->split_var, ft_dl_new(new));
		}
		if (data->str[i])
			pre_expander(data, &i, lst);
	}
}
