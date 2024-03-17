/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/17 13:59:45 by mdomnik          ###   ########.fr       */
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
# include "utils.h"
#define CL_NAME "[minishell]$ "

//ERROR DEFINES
#define ERR_I "Error: too many arguments; launch program with ./minishell and no arguments"
#define ERR_ENV "Error: failed to load environmental variables"


typedef struct s_prompt
{
	char				*line;
	struct s_envll      *envp;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
	struct s_prompt		*next;
	struct s_prompt		*prev;
} 				t_prompt;

typedef struct s_envll
{
	char				**env;
} 				t_envll;

//error_free.c
void simple_err(char *err_str);

#endif
