/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 08:57:15 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 17:01:52 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

enum e_cmd_type
{
	no_quote = 0,
	single_quote = 1,
	double_quotes = 2,
	pre_exp = 3,
	input_redirect = 10,
	here_doc = 11,
	here_doc_quote = 12,
	output_redirect = 13,
	append_redirect = 14,
	piping = 20,
	or = 21,
	and = 22,
	none = 23,
	open_p = 30,
	close_p = 31,
	cmd = 40,
	subs = 41,
	var = 50,
	word = 51
};

enum e_perm
{
	r,
	w,
	x,
	rw,
	rx,
	wx,
	rwx
};

enum e_type
{
	file,
	dir
};

typedef struct s_wildcard
{
	int				pat_i;
	int				str_i;
	int				ast;
	struct s_dlist	*files;
}	t_wildcard;

typedef struct s_cd
{
	char			*start;
	char			*start_oldpwd;
	int				is_change;
	int				argc;
	char			**argv;
	enum e_cmd_type	*argt;
	struct s_dlist	*env;
	int				exec;
	int				exit;
	int				silent;
}	t_cd;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_pre_expand
{
	char			*str;
	enum e_cmd_type	type;
}	t_pre_expand;

typedef struct s_split_cmd
{
	char			*str;
	enum e_cmd_type	type;
	int				connected;
	struct s_dlist	*pre_expand;
}	t_split_cmd;

typedef struct s_computed_cmd
{
	enum e_cmd_type	type;
	int				argc;
	char			**argv;
	struct s_dlist	*wild_argv;
	struct s_dlist	**pre_expand;
	struct s_dlist	*redir;
}	t_computed_cmd;

typedef struct s_exec_cmd
{
	enum e_cmd_type			type;
	enum e_cmd_type			left;
	struct s_computed_cmd	*cmd;
	enum e_cmd_type			right;
	struct s_dlist			*redir;
	int						in_fd;
	int						out_fd;
	int						pipe_fd[2];
	struct s_dlist			*cmds;
	struct s_exec_cmd		*parent;
	int						silent;
	int						exit_status;
}	t_exec_cmd;

typedef struct s_cmds
{
	struct s_dlist		*split_quote;
	struct s_dlist		*split_space;
	struct s_dlist		*split_special;
	struct s_dlist		*split_var;
	struct s_dlist		*connected;
	struct s_dlist		*computed;
	struct s_exec_cmd	*subshell;
}	t_cmds;

typedef struct s_ms
{
	struct s_cmds	cmds;
	struct s_dlist	*env;
	char			*curr_dir;
	pid_t			pids[1024];
	int				last_exit;
	pid_t			last_pipe_pid;
}	t_ms;

#endif
