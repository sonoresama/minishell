# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eorer <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 15:06:08 by eorer             #+#    #+#              #
#    Updated: 2023/09/07 14:40:08 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -I$(INC) -I./include -Wall -Werror -Wextra -g

LFLAGS = -L/usr/local/lib -lreadline

INC = /usr/local/include

HEADER = include/minishell.h 

SRC =	src/main.c					\
	src/main_loop.c					\
	src/sig_handling.c				\
	src/built_in/cd.c				\
	src/built_in/cd_bis.c				\
	src/built_in/check_export.c			\
	src/built_in/echo.c				\
	src/built_in/env.c				\
	src/built_in/exit.c				\
	src/built_in/export.c				\
	src/built_in/ft_built_in.c			\
	src/built_in/pwd.c				\
	src/built_in/unset.c				\
	src/environnement/ft_create_var_env.c		\
	src/environnement/ft_create_var_export.c	\
	src/environnement/ft_env_export.c		\
	src/environnement/ft_join_with_last_error.c	\
	src/environnement/replace_env_var.c		\
	src/environnement/replace_var_env_in_lst.c	\
	src/environnement/update_env.c			\
	src/exec/clear_pipe.c				\
	src/exec/exec_cmd.c				\
	src/exec/exec_cmd_for_child.c			\
	src/exec/ft_heredoc.c				\
	src/exec/pipe_cmd.c				\
	src/parsing/check_pipe.c			\
	src/parsing/cut_quote.c				\
	src/parsing/ft_copy_redir.c			\
	src/parsing/ft_end_set_heredoc.c		\
	src/parsing/ft_end_set_redir.c			\
	src/parsing/get_quote.c				\
	src/parsing/heredoc_redir.c			\
	src/parsing/parsing.c				\
	src/parsing/paste_quote.c			\
	src/parsing/path_cmd.c				\
	src/structure/clear_struct.c			\
	src/structure/ft_fill_cmd.c			\
	src/structure/ft_fill_env.c			\
	src/structure/ft_fill_exec.c			\
	src/structure/ft_fill_parsing.c			\
	src/structure/ft_fill_shell.c			\
	src/structure/init_struct.c			\
	src/utils/lst_utils/ft_init_lst.c		\
	src/utils/lst_utils/ft_lst_add_end.c		\
	src/utils/lst_utils/ft_lst_last.c		\
	src/utils/lst_utils/ft_lstlen.c			\
	src/utils/ft_atoi.c				\
	src/utils/ft_bzero.c				\
	src/utils/ft_close.c				\
	src/utils/ft_double_chrcmp.c			\
	src/utils/ft_free_tab.c				\
	src/utils/ft_itoa.c				\
	src/utils/ft_join_three.c			\
	src/utils/ft_memcpy.c				\
	src/utils/ft_memset.c				\
	src/utils/ft_split_2_separator.c		\
	src/utils/ft_split.c				\
	src/utils/ft_strchr.c				\
	src/utils/ft_strcut.c				\
	src/utils/ft_strdup.c				\
	src/utils/ft_strjoin.c				\
	src/utils/ft_strlen.c				\
	src/utils/ft_strncmp.c				\
	src/utils/ft_strndup.c				\
	src/utils/ft_thereisprint.c			\

OBJ = $(SRC:.c=.o)

NAME = minishell


all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@/bin/rm -f $(OBJ)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
