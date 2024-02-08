# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/14 13:30:32 by gbrunet           #+#    #+#              #
#    Updated: 2024/02/08 10:44:35 by gbrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_RED = \033[0;31m
_GREEN = \033[0;32m
_BLUE = \033[0;34m
_YELLOW = \033[0;33m
_MAGENTA = \033[0;35m
_CYAN = \033[0;36m
_END = \033[0m

NAME = minishell

NAME_BONUS = minishell_bonus

CC = cc

LIBFT = libft

INCLUDES = includes

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -I $(LIBFT)

SRC_DIR = sources/

OBJ_DIR = objects/

PARSING = parsing_quotes parsing_get_quotes parsing_specials subshell \
		  parsing_get_specials parsing_get_redirect parsing_check_parenthesis \
		  parsing_check_redir parsing_check_grammar parsing_create_cmd \
		  parsing_compute_cmd parsing expand expand_utils pre_expand heredoc \
		  heredoc_child set_argc_pre_expand expand_argv subshell_utils \
		  connect_args wildcards

PARSING_FILES = $(addprefix parsing/, $(PARSING))

EXEC = program_utils program_error exec_cmd exec_subshell \
	   files_checking exec_redirect_in exec_redirect_out \
	   exec_cmd_left_right_pipe exec_cmd_right_pipe exec_cmd_left_pipe \
	   exec_cmd_no_pipe exec_redirect_utils get_program

EXEC_FILES = $(addprefix exec/, $(EXEC))

UTILS = minishell free_cmds errors exit env random_char prompt signals \
		intro_fade intro

UTILS_FILES = $(addprefix utils/, $(UTILS))

BUILTIN = utils ft_cd ft_cd_2 ft_cd_pwd ft_cd_path ft_cd_utils ft_echo \
		  ft_pwd ft_env ft_exit ft_unset ft_export ft_export_2 ft_export_utils \
		  exec_builtin_left_right_pipe exec_builtin_left_pipe \
		  exec_builtin_right_pipe exec_builtin_no_pipe

BUILTIN_FILES = $(addprefix builtin/, $(BUILTIN))

DEV = print_subshell

DEV_FILES = $(addprefix dev/, $(DEV))

SRC = main $(PARSING_FILES) $(UTILS_FILES) $(EXEC_FILES) $(BUILTIN_FILES) \
	  $(DEV_FILES)

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

GNL = 0

INTRO = 1

COMPTEUR = 0

.PHONY : all clean fclean re lib norme

all	: $(NAME)

bonus : $(NAME_BONUS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(eval COMPTEUR=$(shell echo $$(($(COMPTEUR)+1))))
	@mkdir -p $(@D)
	@printf "\e[?25l"
	@if test $(COMPTEUR) -eq 1;then \
		printf "$(_YELLOW)Compiling $(NAME) binary files...$(_END)\n\n";fi
	@printf "\033[A\33[2K\r$(_CYAN)Binary $(COMPTEUR): $@$(_END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ -D GNL=$(GNL) -D INTRO=$(INTRO)

$(NAME) : $(OBJ_FILES)
	@make -C $(LIBFT) | grep -v directory
	@$(CC) $(OBJ_FILES) -o $(NAME) -L $(LIBFT) -lft -lreadline
	@echo "$(_GREEN)$(NAME) created$(_END)"
	@printf "\e[?25h"

$(NAME_BONUS) : $(OBJ_FILES)
	@make -C $(LIBFT) | grep -v directory
	@$(CC) $(OBJ_FILES) -o $(NAME_BONUS) -L $(LIBFT) -lft -lreadline
	@echo "$(_GREEN)$(NAME_BONUS) created$(_END)"
	@printf "\e[?25h"


clean : 
	@make clean -C $(LIBFT) | grep -v directory
	@echo "$(_YELLOW)$(NAME): Clean...$(_END)"
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(_GREEN)$(NAME): Binaries deleted...$(_END)"

fclean :
	@make fclean -C $(LIBFT) | grep -v directory
	@echo "$(_YELLOW)$(NAME): Full clean...$(_END)"
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(_GREEN)$(NAME): Binaries deleted...$(_END)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(_GREEN)$(NAME) deleted...$(_END)"

re : fclean all

norme :
	@norminette $(SRC_FILES) | grep -v Norme -B1 || true
	@norminette $(INCLUDES) -R CheckDefine | grep -v Norme -B1 || true
