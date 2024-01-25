/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rallonge.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:31:08 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/25 21:33:24 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//minishell.h

char			*pwd(int argc);
char			*prev(char *paths);
void			free_tab(char **tab);
int				simple_cd(t_cd *data);
t_dlist			*get_env(char **envp);
int				absolut_path(t_cd *data);
int				relative_path(t_cd *data);
void			free_struct_cd(t_cd *data);
char			*get_home_path(t_cd *data);
int 			is_built_in(t_exec_cmd *cmd);
char			*get_oldpwd_path(t_cd *data);
int				ft_chdir(t_cd *data, char *path);
int				change_pwd(t_cd *data, char *new);
char			*add_next(char	*path, char	*name);
int				change_oldpwd(t_cd *data, char *new);
t_dlist			*add_element(char *str, t_dlist *env);
int				cd(int argc, char **argv, t_dlist *env);
int				ft_unset(int argc, char **argv, t_dlist *env);
t_cd			*init_data(int argc, char **argv, t_dlist *env);

//minishell_structs.h

typedef struct s_cd
{
	char	*start;
	int		argc;
	char	**argv;
	t_dlist	*env;
}	t_cd;

