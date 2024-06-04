# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 21:52:00 by kaan              #+#    #+#              #
#    Updated: 2024/06/04 14:33:28 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DEBUG_NAME = minishell_debug

LIBFT = ./lib/libft/libft.a

INC	=  -I inc/

OBJ_DIR	= obj/
DEBUG_OBJ_DIR = debug_obj/


CC = cc

FLAGS = -g -Wall -Wextra -Werror
SANITIZE_FLAGS = -fsanitize=address,undefined


READFLAG = -lreadline

RM = rm -f

SRC =	src/builtin/cd.c\
		src/builtin/echo.c\
		src/builtin/env.c\
		src/builtin/exit.c\
		src/builtin/export.c\
		src/builtin/pwd.c\
		src/builtin/unset.c\
		src/execution/execution.c\
		src/execution/pathexec.c\
		src/expander/expander_process.c\
		src/expander/expander_struct.c\
		src/expander/expander.c\
		src/lexer/lexer_redir.c\
		src/lexer/lexer_struct.c\
		src/lexer/lexer_word.c\
		src/lexer/lexer.c\
		src/main/error_seq.c\
		src/main/main.c\
		src/main/signals.c\
		src/main/testing.c\
		src/parser/parser_node.c\
		src/parser/parser_struct.c\
		src/parser/parser_utils_1.c\
		src/parser/parser_utils_2.c\
		src/parser/parser_utils_3.c\
		src/parser/parser.c\
		src/utils/gen_utils_1.c\
		src/utils/gen_utils_2.c\
		src/utils/gen_utils_3.c\
		src/utils/gen_utils_4.c\
		src/utils/gen_utils_split.c\
		src/builtin/pipe.c\
		src/builtin/redir.c\
		src/builtin/pipex_util_1.c\
		src/builtin/pipex_util_2.c\

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))
DEBUG_OBJ = $(patsubst %.c,$(DEBUG_OBJ_DIR)%.o,$(SRC))


start:
	@make all

$(LIBFT):
	@make -C ./lib/libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIBFT) $(READFLAG) -o $(NAME)

debug: $(DEBUG_NAME)

$(DEBUG_NAME): $(DEBUG_OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(SANITIZE_FLAGS) $(INC) $(DEBUG_OBJ) $(LIBFT) $(READFLAG) -o $(DEBUG_NAME)

$(OBJ_DIR)%.o:		%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

$(DEBUG_OBJ_DIR)%.o:	%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(SANITIZE_FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)  $(DEBUG_OBJ_DIR)
	@make clean -C ./lib/libft

fclean: clean
	@$(RM) $(NAME) $(DEBUG_NAME)
	@$(RM) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRC)

comp: re
	@./$(NAME)

memcheck: re
	@valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=suppressions.supp ./$(NAME)

.PHONY: start all clean fclean re
