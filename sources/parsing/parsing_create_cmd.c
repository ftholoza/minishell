/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:27:22 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:59:59 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_computed_cmd	*create_comp_cmd(enum e_cmd_type type)
{
	t_computed_cmd	*data;

	data = malloc(sizeof(t_computed_cmd));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_computed_cmd));
	data->type = type;
	return (data);
}

t_computed_cmd	*dup_comp_cmd(t_computed_cmd *src)
{
	t_computed_cmd	*dup;

	dup = malloc(sizeof(t_computed_cmd));
	if (!dup)
		return (NULL);
	ft_bzero(dup, sizeof(t_computed_cmd));
	dup->type = src->type;
	dup->argc = src->argc;
	dup->argv = src->argv;
	src->argv = NULL;
	dup->pre_expand = src->pre_expand;
	src->pre_expand = NULL;
	dup->redir = src->redir;
	src->redir = NULL;
	return (dup);
}

t_split_cmd	*create_split_cmd(char *str, enum e_cmd_type type)
{
	t_split_cmd	*data;

	data = malloc(sizeof(t_split_cmd));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_split_cmd));
	data->str = str;
	data->type = type;
	data->connected = 0;
	data->pre_expand = NULL;
	return (data);
}

t_split_cmd	*dup_split_cmd(t_split_cmd *src)
{
	t_split_cmd	*dup;

	dup = malloc(sizeof(t_split_cmd));
	if (!dup)
		return (NULL);
	ft_bzero(dup, sizeof(t_split_cmd));
	dup->type = src->type;
	dup->str = ft_strdup(src->str);
	dup->connected = src->connected;
	dup->pre_expand = src->pre_expand;
	src->pre_expand = NULL;
	return (dup);
}

t_split_cmd	*dup_redir_cmd(t_split_cmd *src, enum e_cmd_type type)
{
	t_split_cmd	*dup;

	dup = malloc(sizeof(t_split_cmd));
	if (!dup)
		return (NULL);
	ft_bzero(dup, sizeof(t_split_cmd));
	dup->type = type;
	dup->str = ft_strdup(src->str);
	dup->connected = src->connected;
	dup->pre_expand = src->pre_expand;
	src->pre_expand = NULL;
	return (dup);
}
