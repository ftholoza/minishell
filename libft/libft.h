/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:57:08 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/20 21:44:32 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_opt
{
	int		minus;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	char	type;
}	t_opt;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

int		is_flag(char c);
int		is_type(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		min(int a, int b);
int		max(int a, int b);
int		ft_isspace(char c);
int		valid_flag(char c);
int		gnl_strlen(char *s);
int		ft_lstsize(t_list *lst);
int		ft_dl_size(t_dlist *list);
int		ft_atoi(const char *nptr);
int		get_endl_pos(char *prev_line);
int		ft_printf(const char *s, ...);
int		ft_free(int return_val, char *str, ...);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_itoa(int n);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	**ft_space_split(char const *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);

void	print_d_num(int nb);
void	print_c_i(char c, int i);
void	*clean_exit(char *p_line);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	init_options(t_opt *options);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	set_type(t_opt *options, char c);
void	set_flags(t_opt *options, char c);
void	print_int_sign(t_opt opts, int d);
void	ft_dl_swap(t_dlist *a, t_dlist *b);
void	*join_str(char *p_line, char *buf);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_dl_add_back(t_dlist **lst, t_dlist *new);
void	ft_dl_add_front(t_dlist **lst, t_dlist *new);
void	ft_dl_del(t_dlist *lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_dl_clear(t_dlist **lst, void (*del)(void *));
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_dl_sort(t_dlist *list, int (*sort_cmp)(void *, void *));

float	minf(float a, float b);
float	maxf(float a, float b);

size_t	ft_intlen(int d);
size_t	x_len(unsigned int nb);
size_t	ft_strlen(const char *s);
size_t	calc_dot(int d, t_opt opts);
size_t	calc_zero(int d, t_opt opts);
size_t	calc_space(int d, t_opt opts);
size_t	calc_nb_size(int d, t_opt opts);
size_t	get_int_size(t_opt opts, int d);
size_t	print_c(t_opt opts, va_list *ap);
size_t	print_s(t_opt opts, va_list *ap);
size_t	print_p(t_opt opts, va_list *ap);
size_t	print_u(t_opt opts, va_list *ap);
size_t	print_x(t_opt opts, va_list *ap);
size_t	print_d(t_opt opts, va_list *ap);
size_t	ft_unsigned_intlen(unsigned int u);
size_t	calc_x_zero(unsigned int x, t_opt opts);
size_t	calc_x_size(unsigned int x, t_opt opts);
size_t	calc_u_zero(unsigned int u, t_opt opts);
size_t	calc_u_space(unsigned int u, t_opt opts);
size_t	calc_x_space(unsigned int x, t_opt opts);
size_t	set_width(const char *s, t_opt *options);
size_t	calc_x_nb_size(unsigned int x, t_opt opts);
size_t	calc_u_nb_size(unsigned int u, t_opt opts);
size_t	set_precision(const char *s, t_opt *options);
size_t	percent_parser(const char *s, t_opt *options);
size_t	get_unsigned_int_size(t_opt opts, unsigned int u);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_dlist	*ft_dl_new(void *data);
t_dlist	*ft_dl_last(t_dlist *lst);
t_dlist	*ft_dl_remove_from(t_dlist **lst, t_dlist *elem, void (*del)(void *));
#endif
