# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.de>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 21:52:00 by kaan              #+#    #+#              #
#    Updated: 2024/02/28 21:52:43 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC	= inc/

SRC_DIR = src/

OBJ_DIR	= obj/

CC = cc

FLAGS = -Wall -Wextra -Werror -I

READFLAG = -lreadline

RM = rm -f

SRC = $(SRC_DIR)*.c\

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(READFLAG) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) .cache_exists

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
