/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:02:44 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/06 15:09:50 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wild_to_argv(t_exec_cmd *cmd)
{
	int		i;
	t_dlist	*lst;

	cmd->cmd->argc = 0;
	lst = cmd->cmd->wild_argv;
	while (lst)
	{
		cmd->cmd->argc += 1;
		lst = lst->next;
	}
	ft_free(0, "s", cmd->cmd->argv);
	cmd->cmd->argv = malloc(sizeof(char *) * (cmd->cmd->argc + 1));
	if (!cmd->cmd->argv)
		return (err(NULL, "malloc error", ERR_MALLOC));
	lst = cmd->cmd->wild_argv;
	i = 0;
	while (lst)
	{
		cmd->cmd->argv[i] = ft_strdup(((t_split_cmd *)lst->data)->str);
		lst = lst->next;
		i++;
	}
	cmd->cmd->argv[i] = NULL;
	ft_dl_clear(&cmd->cmd->wild_argv, &free_split_cmd);
	return (SUCCESS);
}

void	check_wildcards(t_exec_cmd *cmd, int quoted, int i)
{
	t_wildcard	*w;
	t_dlist		*lst;

	w = wildcard(cmd->cmd->argv[i]);
	lst = w->files;
	if (cmd->cmd->argv[0] && ft_strncmp(cmd->cmd->argv[0], "export", 7) != 0
		&& ft_strncmp(cmd->cmd->argv[0], "unset", 6) != 0
		&& lst && !quoted && ft_strchr(cmd->cmd->argv[i], '*'))
	{
		while (lst)
		{
			ft_dl_add_back(&cmd->cmd->wild_argv,
				ft_dl_new(create_split_cmd(ft_strdup(lst->data), no_quote)));
			lst = lst->next;
		}
	}
	else
		ft_dl_add_back(&cmd->cmd->wild_argv, ft_dl_new(create_split_cmd(
					ft_strdup(cmd->cmd->argv[i]), no_quote)));
	ft_dl_clear(&w->files, &free);
	free(w);
}

void	*get_files(t_wildcard *w)
{
	DIR				*dir_fd;
	struct dirent	*dir;
	char			*name_dir;

	name_dir = pwd();
	if (!name_dir)
		return (err_null("minishell: malloc error"));
	dir_fd = opendir(name_dir);
	free(name_dir);
	if (dir_fd == NULL)
	{
		perror("minishell: opendir");
		return (NULL);
	}
	dir = readdir(dir_fd);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
			ft_dl_add_back(&w->files, ft_dl_new(ft_strdup(dir->d_name)));
		dir = readdir(dir_fd);
	}
	closedir(dir_fd);
	return (NULL);
}

int	is_match(char *pattern, char *str, t_wildcard *w)
{
	w->str_i = 0;
	w->pat_i = 0;
	while (str[w->str_i])
	{
		w->ast = 0;
		while (str[w->str_i] && pattern[w->pat_i]
			&& str[w->str_i] == pattern[w->pat_i])
		{
			w->pat_i++;
			w->str_i++;
		}
		while (pattern[w->pat_i] && pattern[w->pat_i] == '*')
		{
			w->ast = 1;
			w->pat_i++;
		}
		while (w->ast && str[w->str_i] && str[w->str_i] != pattern[w->pat_i])
			w->str_i++;
		if (pattern[w->pat_i] == 0 && (pattern[w->pat_i - 1] == '*'
				|| pattern[w->pat_i - 1] == str[ft_strlen(str) - 1]))
			return (SUCCESS);
		if (!w->ast)
			return (FAILURE);
	}
	return (FAILURE);
}

t_wildcard	*wildcard(char *pattern)
{
	t_wildcard	*w;
	t_dlist		*lst;
	t_dlist		*tmp;

	(void)pattern;
	w = malloc(sizeof(t_wildcard));
	if (!w)
		return (err_null("minishell: malloc error"));
	ft_bzero(w, sizeof(t_wildcard));
	get_files(w);
	lst = w->files;
	while (lst)
	{
		if (is_match(pattern, lst->data, w) == FAILURE)
		{
			tmp = lst->next;
			ft_dl_remove_from(&w->files, lst, &free);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	return (w);
}
