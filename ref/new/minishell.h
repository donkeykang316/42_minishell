/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/17 11:26:21 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "lexer.h"
# include "parser.h"

#define CL_NAME "[minishell]$ "

typedef struct s_prompt
{
	char				*line;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
	struct s_prompt		*next;
	struct s_prompt		*prev;
} 				t_prompt;

//Error_free.c
void error_seq(t_global *global, char *error, int xit);

// int ms_loop(t_util *utils, t_token *tokens);
int 	ms_loop(t_global *global);
void	print_lexer(t_global **global);
void	print_parser(t_global **global);


#endif
