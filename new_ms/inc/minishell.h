/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/06 17:57:00 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "builtin.h"
# include "execution.h"
# include "utils.h"

//command line front message
# define CL_NAME "[minishell]$ "

//ERROR DEFINES
# define ERR_I " launch program with ./minishell and no arguments"
# define ERR_SHELL " failed to initialize shell"
# define ERR_ENV " failed to load environmental variables"
# define ERR_MALLOC " failed to allocate memory"
# define ERR_LEXER " failed to initialize lexer node"
# define ERR_EXPAND " failed to initialize expand node"
# define ERR_EMPTY " no nodes found in the lexer list"
# define ERR_INDEX " Index out of range. Cannot delete node"
# define ERR_SYNTAX " syntax error near unexpected token"
# define ERR_QUOTE " quote not terminated by another quote"
# define ERR_CMD " command not found"
# define ERR_NCMD " command not found"
# define ERR_PWD " failed to get current working directory"
# define ERR_PWDA " too many arguments"
# define ERR_ARG " too many arguments"
# define ERR_CD " No such file or directory"
# define ERR_CDARG " too many arguments"
# define ERR_CDHOME "HOME not set"
# define ERR_PATH " failed to find path"
# define ERR_EXP2 " not a valid identifier"
# define ERR_DOLLAR " not valid in this context"
# define ERR_NUM " numeric argument required\n"

/*outermost struct of the shell
  contains all other structs and
  variables needed for the shell to run*/
typedef struct s_shell
{
	char				*line;
	char				**env;
	struct s_expand		*expand;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
	int					std_in;
	int					std_out;
	int					exit_stat;
	char				*cwd;
	pid_t				pid;
}			t_shell;

//util_1
void	free_shell(t_shell *shell, int i);
void	exit_shell(t_data *data, int exit_stat);
void	free_double(char **double_str);

#endif
