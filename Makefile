# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eorer <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 15:06:08 by eorer             #+#    #+#              #
#    Updated: 2023/08/18 14:38:08 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -I$(INC) -I./include -Wall -Werror -Wextra -g

LFLAGS = -L/usr/local/lib -lreadline

INC = /usr/local/include

HEADER = include/minishell.h 

SRC =	src/built_in/cd.c				\
	src/built_in/check_export.c			\
	src/built_in/echo.c				\
	src/built_in/env.c				\
	src/built_in/exit.c				\
	src/built_in/export.c				\
	src/built_in/ft_built_in.c			\
	src/built_in/pwd.c				\
	src/built_in/unset.c				\
	src/exec/exec_cmd.c				\
	src/exec/pipe_cmd.c				\
	src/fill_struct/ft_fill_cmd.c			\
	src/fill_struct/ft_fill_env.c			\
	src/fill_struct/ft_fill_exec.c			\
	src/fill_struct/ft_fill_parsing.c		\
	src/fill_struct/ft_fill_shell.c			\
	src/utils/lst_utils/ft_init_lst.c		\
	src/utils/lst_utils/ft_lst_add_end.c		\
	src/utils/lst_utils/ft_lst_last.c		\
	src/utils/lst_utils/ft_lstlen.c			\
	src/utils/ft_atoi.c				\
	src/utils/ft_bzero.c				\
	src/utils/ft_close.c				\
	src/utils/ft_free_tab.c				\
	src/utils/ft_itoa.c				\
	src/utils/ft_join_three.c			\
	src/utils/ft_memcpy.c				\
	src/utils/ft_memset.c				\
	src/utils/ft_split.c				\
	src/utils/ft_strchr.c				\
	src/utils/ft_strcut.c				\
	src/utils/ft_strdup.c				\
	src/utils/ft_strjoin.c				\
	src/utils/ft_strlen.c				\
	src/utils/ft_strncmp.c				\
	src/utils/ft_strndup.c				\
	src/utils/ft_thereisprint.c			\

SRC += $(wildcard ./src/*.c)

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
