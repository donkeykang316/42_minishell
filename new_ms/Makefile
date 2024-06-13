# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.de>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 21:52:00 by kaan              #+#    #+#              #
#    Updated: 2024/06/13 14:20:02 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./lib/libft/libft.a

INC	= inc/

OBJ_DIR	= obj/

CC = cc

FLAGS = -g -Wall -Wextra -Werror -I

READFLAG = -lreadline

RM = rm -f

SRC =	src/main/testing.c\
		src/main/main.c\
		src/main/ms_init.c\
		src/main/ms_init_util.c\
		src/main/signal.c\
		src/utils/util_1.c\
		src/utils/util_2.c\
		src/utils/util_3.c\
		src/utils/util_4.c\
		src/parser/pre_process.c\
		src/parser/syntax.c\
		src/parser/syntax_util.c\
		src/parser/expander.c\
		src/parser/expander_util.c\
		src/parser/parser.c\
		src/parser/parser_util.c\
		src/parser/tokenizer.c\
		src/execution/execution.c\
		src/execution/exit.c\
		src/execution/cd.c\
		src/execution/cd_util.c\
		src/execution/env.c\
		src/execution/echo.c\
		src/execution/pwd.c\
		src/execution/unset.c\
		src/execution/export.c\

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

start:
	@make all

$(LIBFT):
	@make -C ./lib/libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIBFT) $(READFLAG) -o $(NAME)

$(OBJ_DIR)%.o:		%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./lib/libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRC)

comp: re
	@./$(NAME)

memcheck: re
	@valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=suppressions.supp ./$(NAME)

.PHONY: start all clean fclean re
