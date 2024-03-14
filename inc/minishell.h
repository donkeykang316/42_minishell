/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/14 16:57:32 by mdomnik          ###   ########.fr       */
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

typedef struct s_global
{
	char				*prompt;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
} 				t_global;

//Error_free.c
void error_seq(t_global *global, char *error, int xit);

// int ms_loop(t_util *utils, t_token *tokens);
int 	ms_loop(t_global *global);
void	print_lexer(t_global **global);
void	print_parser(t_global **global);


#endif
