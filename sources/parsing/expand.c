/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:22:05 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/05 17:32:58 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_custom(char c, t_dlist *split, int *i)
{
	t_ms	*ms;
	char	*exit;

	ms = get_ms();
	exit = ft_itoa(ms->last_exit);
	if (c == '0')
	{
		ft_dl_add_back(&split, ft_dl_new(ft_strdup("minishell")));
		(*i)++;
	}
	else if (c == '?')
	{
		ft_dl_add_back(&split, ft_dl_new(ft_strdup(exit)));
		(*i)++;
	}
	else if (c == '$')
	{
		ft_dl_add_back(&split, ft_dl_new(ft_strdup("$$")));
		(*i)++;
	}
	else
		ft_dl_add_back(&split, ft_dl_new(ft_strdup("$")));
	free(exit);
}

void	expander(t_split_cmd *data, t_dlist *split, int *i)
{
	int		start;
	char	*value;
	char	*var;

	(*i)++;
	start = *i;
	if (is_custom_expand(data->str[*i]))
		expand_custom(data->str[*i], split, i);
	else
	{
		while (data->str[*i] && is_var_char(data->str[*i]))
			(*i)++;
		var = ft_substr(data->str, start, *i - start);
		value = ft_getenv(var);
		free(var);
		if (value)
			ft_dl_add_back(&split, ft_dl_new(ft_strdup(value)));
	}
}

void	save_expand(t_split_cmd *data, t_dlist *split)
{
	char	*out;
	t_dlist	*tmp;

	out = ft_strdup("");
	tmp = split;
	while (tmp)
	{
		out = ft_str_append(out, tmp->data);
		tmp = tmp->next;
	}
	free(data->str);
	ft_dl_clear(&split, &free);
	data->str = out;
}

void	expand(t_split_cmd *data)
{
	int		i;
	int		start;
	t_dlist	*split;

	split = NULL;
	i = 0;
	while (data->str[i])
	{
		start = i;
		while (data->str[i] && data->str[i] != '$')
			i++;
		ft_dl_add_back(&split,
			ft_dl_new(ft_substr(data->str, start, i - start)));
		if (data->str[i])
			expander(data, split, &i);
	}
	save_expand(data, split);
}
