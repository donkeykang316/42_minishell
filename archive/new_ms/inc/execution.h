/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:25 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 13:34:38 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_shell	t_shell;

//execution
void	execution(t_shell *shell);
bool	is_valid_id(char *token);
bool	input_redir_check(t_parser *parser);
bool	pipe_check(t_parser *parser);

//builtin
void	single_exe(t_shell *shell, t_parser *parser);
void	cmd_exit(t_shell *shell, t_parser *parser);
int 	cmd_cd(t_shell *shell, t_parser *parser);
int	    cd_util(char *path, t_shell *shell);
int	    cmd_env(t_shell *shell);
int	    cmd_echo(t_parser *parser);
int	    cmd_pwd(void);
int     cmd_unset(t_shell *shell, t_parser *parser);
int     cmd_export(t_shell *shell, t_parser *parser);
void	find_path(t_shell *shell, t_parser *parser);

//pipe & redirection
void	exec_cmd(t_shell *shell, t_parser *parser);
void	pipe_exe(t_shell *shell, t_parser *parser);
void	redir_exe(t_shell *shell, t_parser *parser);
void	less_nofile(void);
void	less_nopermit_exit(t_shell *shell);
void	less_multi_file(t_shell *shell, t_parser *parser, int fd);
void	less_one_file(t_shell *shell, t_parser *parser, int fd);
void	less_invalid_input(char *token);

#endif
