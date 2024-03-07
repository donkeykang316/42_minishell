/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:00:18 by kaan              #+#    #+#             */
/*   Updated: 2024/03/07 12:26:45 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ab_path(char *str, t_cd *var)
{
	var->dpath = ft_substr(str, ft_strlen(var->pwd), ft_strlen(str));
	ft_chdir(str, var->dpath);
	free(var->dpath);
}

static void	re_path(char *str, t_cd *var)
{
	var->len = 3;
	while (str[var->len] == 32)
		var->len++;
	var->dpath = ft_substr(str, var->len, ft_strlen(str));
	ft_chdir(str, var->dpath);
	free(var->dpath);
}

static void	cd_back(char *str, t_cd *var)
{
	var->len = ft_strlen(var->pwd);
	while (var->pwd[var->len] != 47)
		var->len--;
	var->pwd[var->len] = '\0';
	ft_chdir(str, var->pwd);
}

static void	quotation_cd(char *str, int c, t_cd *var)
{
	int	i;

	i = 0;
	if (c)
	{
		while (str[i])
		{
			if (str[i] == c)
				str[i] = 32;
			i++;
		}
	}
	if (ft_strnstr(str, " .. ", ft_strlen(str)))
		cd_back(str, var);
	else if (!ft_memcmp(var->pwd, str, ft_strlen(var->pwd)))
		ab_path(str, var);
	else
		re_path(str, var);
}

void	ft_cd(char *str)
{
	t_cd	var;

	cd_init(&var);
	var.pwd = getcwd(NULL, 0);
	var.len = 0;
	if (ft_strchr(str, 34))
		quotation_cd(str, 34, &var);
	else if (ft_strchr(str, 39))
		quotation_cd(str, 34, &var);
	else
		quotation_cd(str, 0, &var);
	free(var.pwd);
	free(str);
}
