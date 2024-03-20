/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:00:18 by kaan              #+#    #+#             */
/*   Updated: 2024/03/08 09:19:02 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	str_len_i(char *str, int c, t_cd *var)
{
	while (str[var->i])
	{
		if (str[var->i] == c)
			break ;
		var->i++;
	}
	var->i++;
	var->len = ft_strlen(str);
	while (var->len > 0)
	{
		if (str[var->len] == c)
			break ;
		var->len--;
	}
	var->len--;
}

static void	quotation_cd(char *str, int c, t_cd *var)
{
	if (c)
	{
		str_len_i(str, c, var);
		if (ft_strnstr(str, "..", ft_strlen(str)))
			cd_back(str, c, var);
		else if (!ft_memcmp(var->pwd, str, ft_strlen(var->pwd)))
			ab_path(str, c, var);
		else
			re_path(str, c, var);
	}
	else
	{
		if (ft_strnstr(str, " .. ", ft_strlen(str)))
			cd_back(str, c, var);
		else if (!ft_memcmp(var->pwd, str, ft_strlen(var->pwd)))
			ab_path(str, c, var);
		else
			re_path(str, c, var);
	}

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
