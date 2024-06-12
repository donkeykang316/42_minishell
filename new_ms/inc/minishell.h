/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:52:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 19:36:49 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <bsd/string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "parsing.h"
# include "execution.h"

//command line front message
# define CL_NAME "[minishell]$ "

/* CONSTANTS */

# define SUCCESS 0
# define FAILURE -1
# define OPERATORS "|<>"
# define QUOTES "\"\'"
# define DELIMS "\"\' "
# define REDIRECTS "><"

/* ERROR MESSAGES */

// MINISHELL
# define CL_ARGUMENTS_ERR "minishell: no support for command-line arguments"
# define NO_PIPE_PROMPT "minishell: no support for pipe prompt"
# define NO_SYTX_PROMPT "minishell: no support for syntax prompt"
# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"

// SYNTAX
# define UNCLOSED_QUOTES "minishell: unclosed quotes"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token '"
# define SYTX_ERR_RDR "minishell: syntax error near unexpected token"

// EXIT CMD
# define EXIT_TOO_MANY_ARGS "minishell: exit: too many arguments"
# define EXIT_NON_NUMERIC_ARG "minishell: exit: numeric argument required" 

// CD CMD
# define PATH_MAX	4096
# define CD_TOO_MANY_ARGS "minishell: cd: too many arguments"
# define OLDPWD_NOT_SET "minishell: cd: OLDPWD not set"

typedef enum e_operator
{
	NONE,
	GREAT,
	APPEND,
	LESS,
	HEREDOC,
	PIPE,
}				t_operator;

typedef struct s_parser
{
	int					token_count;
	char				**token;
	t_operator			operator;
	struct s_parser		*next;
}				t_parser;

typedef struct s_vlst
{
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}				t_vlst;

typedef struct s_shell
{
	char		**envp;
	t_vlst		*envp_lst;
	t_parser	*parser;
}				t_shell;

//expander util
static inline bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}

//testing
void	print_vlist(t_vlst **list);
void    print_parser(t_parser *parser);

//init
void	shell_init(char **envp, t_shell *shell, t_parser **s_parser);
void	init_oldpwd(t_vlst **head);
char	**split_envp(char *envp);

//signal
void	config_signals(void);
void	child_signals(int signum);

//utils
void	exit_shell(t_shell *shell, char *msg, int exit_status);
bool	strcmp_ms(char *s1, char *s2);
bool	unexpected_token(char token);
int		unset_var(char *var_name, t_vlst **head);
t_vlst	*v_new_node(char *var_name, char *var_value, bool is_exported);
t_vlst	*v_lstlast(t_vlst *node);
void	v_lstadd_back(t_vlst **head, t_vlst *new);
char	*get_fromvlst(char *var_name, t_vlst **head);
char	*get_varvalue_fromvlst(char *var_name, t_shell *shell);

#endif
