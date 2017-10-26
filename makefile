# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/30 17:53:40 by jamerlin          #+#    #+#              #
#    Updated: 2017/10/26 11:41:02 by jamerlin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = -I ./includes

LIB = -I ./libft -L ./libft/ -lft

SRC = srcs/main.c \
	  srcs/cd_builltin.c \
	  srcs/tool.c \
	  srcs/split_arg.c \
	  srcs/env.c \
	  srcs/echo.c \
	  srcs/tools_two.c \
	  srcs/create_env.c \
	  srcs/exec_cmd.c \
	  srcs/print.c \
	  srcs/setenv.c \
	  srcs/display_prompt.c \
	  srcs/memory_managment.c \
	  srcs/parse.c \
	  srcs/replace.c \
	  srcs/tools_three.c \
	  srcs/unsetenv.c \
	  srcs/exec_cmd_two.c \
	  srcs/utils_cd.c \
	  srcs/run_cmd.c \

CC = gcc -I./includes #-fsanitize=address -g3

OPTION = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(OPTION) -o $(NAME) -g $(OBJ) $(LIB) $(HEADER)

all : $(NAME)

clean :
	rm -f $(OBJ)
	make clean -C libft

fclean : clean
	rm -f $(NAME)
	make fclean -C libft/

re : fclean all
