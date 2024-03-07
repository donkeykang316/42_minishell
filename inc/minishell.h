/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/07 12:03:18 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_echo
{
	char	*pr;
	char	*temp1;
	char	*temp2;
	int		i;
}	t_echo;

typedef struct s_cd
{
	char	*pwd;
	char	*dpath;
	int		len;
}	t_cd;

void	ft_echo(char *str);
void	echo_init(t_echo *var);
void	free_echo(t_echo *var);

void	ft_pwd(char *str);

void	ft_cd(char *str);
void	cd_init(t_cd *var);
void	ft_chdir(char *str, char *pwd);

#endif
