/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:05:51 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/07 17:04:51 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "minishell_structs.h"

# ifndef GNL
#  define GNL 0
# endif
# ifndef INTRO
#  define INTRO 1
# endif

# define ERR_PERM -12
# define ERR_FILE -11
# define ERR_PIPE -10
# define ERR_OPEN -9
# define ERR_READ -8
# define ERR_RAND -7
# define ERR_ENV -6
# define ERR_FORK -5
# define ERR_EMPTY_CMD -4
# define ERR_MALLOC -3
# define ERR_PARSING -2
# define ERR_QUOTE -1
# define SUCCESS 0
# define FAILURE 1

int				ft_abs(int a);
int				hd_err(char *str);
int				check_redir(void);
int				compute_cmds(void);
int				is_var_char(char c);
int				check_grammar(void);
int				check_arg(char *arg);
int				parse_cmd(char *str);
int				simple_cd(t_cd *data);
int				next_in(t_dlist *lst);
int				path_error(char *path);
int				next_out(t_dlist *lst);
int				ft_cd(t_exec_cmd *cmd);
int				check_read(char *path);
int				ft_pwd(t_exec_cmd *cmd);
int				point_point(t_cd *data);
int				check_write(char *path);
int				check_exist(char *path);
int				ft_env(t_exec_cmd *cmd);
int				ft_is_forbidden(char c);
int				parse_cmd_special(void);
int				check_parenthesis(void);
int				ft_exit(t_exec_cmd *cmd);
int				is_custom_expand(char c);
int				ft_echo(t_exec_cmd *cmd);
int				ft_unset(t_exec_cmd *cmd);
int				ft_export(t_exec_cmd *cmd);
int				init_minishell(char **env);
int				parse_cmd_var(t_dlist *lst);
int				is_builtin(t_exec_cmd *cmd);
int				expand_hd(t_split_cmd *cmd);
int				close_fds_err(t_dlist *lst);
int				check_plus(char	*arg, int i);
int				wild_to_argv(t_exec_cmd *cmd);
int				parse_cmd_parts(t_cmds *cmds);
int				process_redir(t_exec_cmd *cmd);
int				get_cmd_part(char *str, int i);
int				hd_rl(t_split_cmd *cmd, int fd);
int				hd_gnl(t_split_cmd *cmd, int fd);
int				wave_path(t_cd *data, int *exit);
int				ft_chdir(t_cd *data, char *path);
int				save_hd(t_split_cmd *cmd, int fd);
int				enter_dir(char *name, t_cd *data);
int				change_pwd(t_cd *data, char *new);
int				process_in_redir(t_exec_cmd *cmd);
int				process_out_redir(t_exec_cmd *cmd);
int				add_to_env(char *name, char *value);
int				absolut_path(t_cd *data, int *exit);
int				relative_path(t_cd *data, int *exit);
int				change_oldpwd(t_cd *data, char *new);
int				split_no_quote_cmd(t_split_cmd *data);
int				check_perm(char *path, enum e_perm p);
int				check_type(char *path, enum e_type t);
int				options(char **args, t_cd *data, int i);
int				err_not_valid(char *str, t_exec_cmd *cmd);
int				trust_the_process(char *name, char *value);
int				err(char *file, char *str, int return_val);
int				get_open_p(t_cmds *cmds, char *str, int i);
int				execute_cmd(t_exec_cmd *cmd, t_dlist *lst);
int				exec_no_pipe(t_exec_cmd *cmd, t_dlist *lst);
int				get_close_p(t_cmds *cmds, char *str, int i);
int				get_no_quote_cmd(char *str, int i, int len);
int				wave_home(t_cd *data, char *home, int *exit);
int				proc_in_redir(int *in_fd, t_split_cmd *data);
int				exec_left_pipe(t_exec_cmd *cmd, t_dlist *lst);
int				exec_right_pipe(t_exec_cmd *cmd, t_dlist *lst);
int				get_single_quote_cmd(char *str, int i, int len);
int				get_and(t_cmds *cmds, char *str, int i, int len);
int				get_double_quotes_cmd(char *str, int i, int len);
int				proc_output_redir(int *out_fd, t_split_cmd *data);
int				proc_append_redir(int *out_fd, t_split_cmd *data);
int				exec_no_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
					int (*builtin)(t_exec_cmd *));
int				get_piping(t_cmds *cmds, char *str, int i, int len);
int				exec_left_right_pipe(t_exec_cmd *cmd, t_dlist *lst);
int				exec_right_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
					int (*builtin)(t_exec_cmd *));
int				exec_left_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
					int (*builtin)(t_exec_cmd*));
int				exec_left_right_pipe_builtin(t_exec_cmd *cmd, t_dlist *lst,
					int (*builtin)(t_exec_cmd *));
int				get_input_redirect(t_cmds *cmds, char *str, int i, int len);
int				get_output_redirect(t_cmds *cmds, char *str, int i, int len);
int				browse_redir_lst(t_split_cmd *data, int *out_fd, t_dlist *lst);

void			intro(void);
void			ms_rl(void);
void			ms_gnl(void);
void			close_fd(int *fd);
void			add_pid(pid_t pid);
void			close_all_fds(void);
void			clear_cmds_lst(void);
void			free_env(void *data);
void			*err_null(char *str);
void			close_fds(t_dlist *lst);
void			connect_pre_ex_argv(void);
void			expand(t_split_cmd *data);
void			handle_signal(int signum);
void			heredoc(t_split_cmd *cmd);
void			update_signal(int signum);
void			free_struct_cd(t_cd *data);
void			connect_args(t_dlist *lst);
void			exec_prog(t_exec_cmd *cmd);
void			free_split_cmd(void *data);
void			full_exit(int return_value);
void			expand_args(t_exec_cmd *cmd);
void			handle_hd_signal(int signum);
void			update_signal_hd(int signum);
void			wait_childs(t_exec_cmd *cmd);
void			unlink_all(t_exec_cmd *subs);
void			filename_arg(t_exec_cmd *cmd);
void			no_such_file(t_exec_cmd *cmd);
void			free_computed_cmd(void *data);
void			update_connected(t_dlist *lst);
void			handle_child_signal(int signum);
void			exec_shell(t_exec_cmd *subshell);
void			random_char_in(struct winsize w);
void			ft_expander(t_split_cmd *pre_ex);
void			command_not_found(t_exec_cmd *cmd);
void			permission_denied(t_exec_cmd *cmd);
void			print_subshell(t_exec_cmd *subshell);
void			update_exit(t_exec_cmd *cmd, int new_exit);
void			pre_expand(t_split_cmd *data, t_dlist *lst);
void			exec_builtin(t_exec_cmd *cmd, t_dlist *lst);
void			random_char_out(struct winsize w, char **title);
void			*save_cmd(t_dlist **lst, t_exec_cmd *parent,
					t_computed_cmd **data, enum e_cmd_type left);
void			set_cmd_argc(t_dlist *lst, t_computed_cmd *cmd);
void			set_cmd_redir(t_dlist *lst, t_computed_cmd *cmd);
void			check_wildcards(t_exec_cmd *cmd, int quoted, int i);
void			init_subs(t_exec_cmd *new, enum e_cmd_type left,
					t_exec_cmd *parent);
void			*create_subs_open_p(t_dlist **lst, t_exec_cmd *parent,
					t_computed_cmd **data, enum e_cmd_type left);
void			expand_redir(int *quote, t_dlist *lst, t_split_cmd *data);
void			set_subshell_redir(t_exec_cmd *new, t_computed_cmd **data,
					t_dlist **lst);

char			*pwd(void);
char			*get_prompt(void);
char			*prev(char *paths);
char			**env_to_array(void);
char			*ft_getenv(char *name);
char			*extract_name(char *arg);
char			*extract_value(char *arg);
char			*get_home_path(t_cd *data);
char			*get_oldpwd_path(t_cd *data);
char			*get_random_char(int nb_char);
char			*cmd_type(enum e_cmd_type type);
char			*add_path(char *path, char *str);
char			*ft_str_append(char *str, char *add);
char			*get_prog(char *name, int *perm_denied);

t_ms			*get_ms(void);

t_cmds			*get_cmds(void);

t_dlist			*wildcard_redir(t_split_cmd *data, int *quote);
t_dlist			*set_cmd_pre_expand(t_dlist *lst, t_computed_cmd *cmd);

t_wildcard		*wildcard(char *patern);

t_exec_cmd		*create_subshell(t_dlist *lst);

t_split_cmd		*dup_split_cmd(t_split_cmd *src);
t_split_cmd		*create_split_cmd(char *str, enum e_cmd_type type);
t_split_cmd		*dup_redir_cmd(t_split_cmd *src, enum e_cmd_type type);

t_pre_expand	*create_pre_expand(char *str, enum e_cmd_type type);

t_computed_cmd	*dup_comp_cmd(t_computed_cmd *src);
t_computed_cmd	*create_comp_cmd(enum e_cmd_type type);

enum e_cmd_type	is_special(char c);
enum e_cmd_type	get_cmd_quote(char c);
enum e_cmd_type	last_op(t_dlist *lst);

#endif
