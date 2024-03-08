/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:52:14 by kaan              #+#    #+#             */
/*   Updated: 2024/03/07 17:13:47 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cd_init(t_cd *var)
{
	var->dpath = NULL;
	var->pwd = NULL;
	var->len = 0;
	var->i = 0;
}

void	ft_chdir(char *str, char *pwd)
{
	if (chdir(pwd))
		printf("%s: No such directory\n", str);
}

void	ab_path(char *str, int c, t_cd *var)
{
	(void)c;
	var->dpath = ft_substr(str, ft_strlen(var->pwd), ft_strlen(str));
	ft_chdir(str, var->dpath);
	free(var->dpath);
}

void	re_path(char *str, int c, t_cd *var)
{
	(void)c;
	var->len = 3;
	while (str[var->len] == 32)
		var->len++;
	var->dpath = ft_substr(str, var->len, ft_strlen(str));
	ft_chdir(str, var->dpath);
	free(var->dpath);
}

void	cd_back(char *str, int c, t_cd *var)
{
	if (c)
	{
		var->dpath = ft_substr(str, var->i, var->len - 5);
		printf("ERROR:%s\n", var->dpath);
		free(var->dpath);
	}
	else
	{
		var->len = ft_strlen(var->pwd);
		while (var->pwd[var->len] != 47)
			var->len--;
		var->pwd[var->len] = '\0';
		ft_chdir(str, var->pwd);
	}
}
