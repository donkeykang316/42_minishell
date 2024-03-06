/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:00:18 by kaan              #+#    #+#             */
/*   Updated: 2024/03/06 18:29:13 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_chdir(char *str, char *pwd)
{
	if (chdir(pwd))
		printf("%s: No such directory\n", str);
}

static void	cd_back(char *str, char *pwd, int len)
{
	len = ft_strlen(pwd);
	while (pwd[len] != 47)
		len--;
	pwd[len] = '\0';
	ft_chdir(str, pwd);
}

void	ft_cd(char *str)
{
	char	*pwd;
	char	*dpath;
	int		len;

	pwd = getcwd(NULL, 0);
	len = 0;
	if (ft_strnstr(str, "..", ft_strlen(str)))
		cd_back(str, pwd, len);
	else if (!ft_memcmp(pwd, str, ft_strlen(pwd)))
	{
		dpath = ft_substr(str, ft_strlen(pwd), ft_strlen(str));
		ft_chdir(str, dpath);
		free(dpath);
	}
	else
	{
		len = 3;
		while (str[len] == 32)
			len++;
		dpath = ft_substr(str, len, ft_strlen(str));
		ft_chdir(str, dpath);
		free(dpath);
	}
	free(pwd);
	free(str);
}
