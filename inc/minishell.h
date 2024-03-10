/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:11 by kaan              #+#    #+#             */
/*   Updated: 2024/03/10 10:19:56 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <../inc/parsing.h>

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

int	builtin_command(char *str, char *temp);

void	ft_echo(char *str);
void	echo_init(t_echo *var);
void	free_echo(t_echo *var);

void	ft_pwd(char *str);

void	ft_cd(char *str);
void	cd_init(t_cd *var);
void	ft_chdir(char *str, char *pwd);


//ft_env.c
void ft_env(char *str);

#endif
