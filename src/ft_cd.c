/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:00:18 by kaan              #+#    #+#             */
/*   Updated: 2024/03/06 15:23:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_chdir(char *str, char *pwd)
{
	if (chdir(pwd))
		printf("%s: No such directory\n", str);
}

void	ft_cd(char *str)
{
	char	*pwd;
	int		len;

	if (ft_strnstr(str, "..", ft_strlen(str)))
	{
		pwd = getcwd(NULL, 0);
		len = ft_strlen(pwd);
		while (pwd[len] != 47)
			len--;
		pwd[len] = '\0';
		ft_chdir(str, pwd);
		free(pwd);
	}
	else
	{
		len = 3;
		while (str[len] == 32)
			len++;
		pwd = ft_substr(str, len, ft_strlen(str));
		ft_chdir(str, pwd);
		free(pwd);
	}
	free(str);
}
