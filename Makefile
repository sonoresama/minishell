# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eorer <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 15:06:08 by eorer             #+#    #+#              #
#    Updated: 2023/05/16 16:36:08 by bastien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -I$(INC) -I./include/ -Wall -Werror -Wextra

LFLAGS = -L/usr/local/lib -lreadline

INC = /usr/local/include

HEADER = include/minishell.h 

SRC = 	./src/ft_split.c	\
	./src/test.c		\
	./src/utils.c		\
	./src/utils2.c		\
	./src/check_path.c	\
	./src/parsing.c		\


OBJ = $(SRC:.c=.o)


NAME = minishell


all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@/bin/rm -f $(OBJ)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
