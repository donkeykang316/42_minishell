/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:35:25 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 14:55:45 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_shell	t_shell;

//execution
void	execution(t_shell *shell);

//builtin
void	cmd_exit(t_shell *shell);
int 	cmd_cd(t_shell *shell);
int	    cd_util(char *path, t_shell *shell);
int	    cmd_env(t_shell *shell);
int	    cmd_echo(t_shell *shell);
int	    cmd_pwd(void);
int     cmd_unset(t_shell *shell);
int     cmd_export(t_shell *shell);
bool	is_valid_id(char *token);

#endif
