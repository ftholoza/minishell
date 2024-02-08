# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 10:00:18 by gbrunet           #+#    #+#              #
#    Updated: 2024/01/31 17:11:28 by gbrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_RED = \033[0;31m
_GREEN = \033[0;32m
_BLUE = \033[0;34m
_YELLOW = \033[0;33m
_MAGENTA = \033[0;35m
_CYAN = \033[0;36m
_END = \033[0m

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_isspace.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c \
		ft_split.c ft_space_split.c ft_free.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_printf.c options.c percent_parcer.c print_c.c print_s.c print_p.c \
		print_d.c print_u.c print_x.c print_x_helper.c helper.c \
		print_d_helper.c print_u_helper.c get_next_line.c \
		get_next_line_utils.c maths_func.c ft_dl_new.c ft_dl_add_front.c \
		ft_dl_add_back.c ft_dl_del.c ft_dl_clear.c ft_dl_new.c ft_dl_last.c \
		ft_dl_size.c ft_dl_sort.c ft_dl_swap.c ft_dl_remove_from.c

ALLSRCS = $(SOURCES) $(BONUS)

OBJECTS = $(SOURCES:.c=.o)

ALLOBJS = $(ALLSRCS:.c=.o)

COMPTEUR = 0

%.o : %.c
	$(eval COMPTEUR=$(shell echo $$(($(COMPTEUR)+1))))
	@printf "\e[?25l"
	@if test $(COMPTEUR) -eq 1;then \
		printf "$(_YELLOW)Compiling $(NAME) binary files...$(_END)\n\n";fi
	@printf "\033[A\33[2K\r$(_CYAN)Binary $(COMPTEUR): $@$(_END)\n"
	@$(CC) -c $(CFLAGS) $< -o $@ -I ./

.PHONY : all clean fclean re bonus

$(NAME) : $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@echo "$(_GREEN)Libft created$(_END)"
	@printf "\e[?25h"

all : $(NAME)

clean :
	@echo "$(_YELLOW)$(NAME): Clean...$(_END)"
	@$(RM) $(ALLOBJS)
	@echo "$(_GREEN)$(NAME): Binaries deleted...$(_END)"

fclean :
	@echo "$(_YELLOW)$(NAME): Full clean...$(_END)"
	@$(RM) $(ALLOBJS)
	@echo "$(_GREEN)$(NAME): Binaries deleted...$(_END)"
	@$(RM) $(NAME)
	@echo "$(_GREEN)$(NAME) deleted...$(_END)"

re : fclean all

