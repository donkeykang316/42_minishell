/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:52:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 13:09:03 by kaan             ###   ########.fr       */
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
# define EXIT_TOO_MANY_ARGS "exit: too many arguments"
# define EXIT_NON_NUMERIC_ARG "exit: numeric argument required" 

// CD CMD
# define PATH_MAX	4096
# define CD_TOO_MANY_ARGS "cd: too many arguments"
# define OLDPWD_NOT_SET "cd: OLDPWD not set"

//READ FILE
# define NO_FILE " No such file or directory"
# define NO_PERMIT " Permission denied"

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

typedef struct s_envp
{
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_envp	*next;
}				t_envp;

typedef struct s_shell
{
	char		**envp;
	t_envp		*envp_lst;
	t_parser	*parser;
	bool		more_redir_pipe;
}				t_shell;

//testing
void	print_envp(t_envp **envp);
void    print_parser(t_parser *parser);
void    print_token(char **token);

//init
void	shell_init(char **envp, t_shell *shell);
void	init_oldpwd(t_envp **head);
char	**split_envp(char *envp);
int		save_user_vars(char *statement, t_envp **envp, bool to_export);

//signal
void	config_signals(void);
void	child_signals(int signum);

//utils
void	exit_shell(t_shell *shell, char *msg, int exit_status);
void	destroy(t_shell *shell);
void	free_d_lst(char **list);
bool	strcmp_ms(char *s1, char *s2);
bool	unexpected_token(char token);
int		unset_var(char *var_name, t_envp **envp);
t_envp	*envp_new_node(char *var_name, char *var_value, bool is_exported);
t_envp	*envp_last(t_envp *node);
void	envp_add_back(t_envp **envp, t_envp *new);
char	*get_envp(char *var_name, t_envp **envp);
char	*get_varvalue_envp(char *var_name, t_shell *shell);
size_t	parser_size(t_parser *parser);
bool	ft_isnum(char *str);
char	*ft_strjoin_ms(char *s1, char *s2);
void	envp_clean(t_envp **list);
void	parser_clean(t_parser **parser);

#endif
