/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:01:29 by kaan              #+#    #+#             */
/*   Updated: 2024/04/14 04:56:13 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "minishell.h"

typedef struct	s_tmp
{
	char	*temp;
	char	*temp1;
	char	*path;
	char	**all_path;
	int	i;
}		t_tmp;

void	exe_main(t_prompt *prompt);
void    ft_echo(t_prompt *prompt);
void	ft_pwd(t_prompt *prompt);
void	ft_cd(t_prompt *prompt);
void	ft_exit(char *error);

#endif
