/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:25 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 17:07:27 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_shell	t_shell;

//execution
void	execution(t_shell *shell);
bool	is_valid_id(char *token);

//builtin
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

#endif
