/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:01:29 by kaan              #+#    #+#             */
/*   Updated: 2024/04/16 09:41:35 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "minishell.h"

typedef struct	s_tmp
{
	char	*temp;
	char	*s_char;
	char	**d_char;
	int	i;
}		t_tmp;

void	exe_main(t_prompt *prompt);
void    ft_echo(t_prompt *prompt);
void	ft_pwd(t_prompt *prompt);
void	ft_cd(t_prompt *prompt);
void	ft_env(t_prompt *prompt);
void	operator_dollar(t_prompt *prompt);
void	cmd_exit(t_prompt *prompt);
void	ft_exit(char *error);
void	free_double_ptr(char **ptr);

#endif
