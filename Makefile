# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eorer <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 15:06:08 by eorer             #+#    #+#              #
#    Updated: 2023/08/17 16:04:55 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -I$(INC) -I./include -Wall -Werror -Wextra -g

LFLAGS = -L/usr/local/lib -lreadline

INC = /usr/local/include

HEADER = include/minishell.h 

SRC = src/exec/exec_cmd.c \
	src/exec/pipe_cmd.c \
	src/utils/ft_itoa.c \
	src/utils/ft_atoi.c \
	src/utils/strchr.c \
	src/utils/ft_split.c \
	src/utils/utilities_1.c \
	src/utils/utilities_2.c \
	src/utils/utilities_3.c \
	src/utils/utilities_lst.c \
	src/built_in/cd.c \
	src/built_in/check_export.c \
	src/built_in/echo.c \
	src/built_in/env.c \
	src/built_in/exit.c \
	src/built_in/export.c \
	src/built_in/pwd.c \
	src/built_in/unset.c \
	src/built_in/ft_built_in.c

SRC += $(wildcard ./src/*.c)

OBJ = $(SRC:.c=.o)

#OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

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
