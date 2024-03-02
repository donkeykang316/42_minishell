/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/03/02 06:44:31 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo_n(const char *str)
{
	char	*pr;

	pr = ft_substr(str, 8, ft_strlen(str));
	printf("%s%c\n", pr, '%');
	free(pr);
}

static void	quatation_case(const char *str, int c, char *pr)
{
	static char	*stemp = NULL;
	char		*temp;
	int			len;

	if (str[ft_strlen(str) - 1] == c)
	{
		len = ft_strlen(str);
		pr = ft_memchr(str, str[6], len - 1);
		pr[ft_strlen(pr) - 1] = '\0';
		printf("%s\n", pr);
		return ;
	}
	else
	{
		temp = NULL;
		stemp = ft_strdup(str);
		while (1)
		{
			temp = readline("quote> ");
			stemp = ft_strjoin(stemp, temp);
			free(temp);
			if (stemp[ft_strlen(stemp) - 1] == c)
			{
				len = ft_strlen(stemp);
				pr = ft_memchr(stemp, stemp[6], len - 1);
				pr[ft_strlen(pr) - 1] = '\0';
				printf("%s\n", pr);
				free(stemp);
				return ;
			}
		}
	}
}

void	ft_echo(const char *str)
{
	char	*pr;

	pr = NULL;
	if (ft_strchr(str, 34))
		quatation_case(str, 34, pr);
	else if (ft_strchr(str, 39))
		quatation_case(str, 39, pr);
	else
	{
		pr = ft_substr(str, 5, ft_strlen(str));
		printf("%s\n", pr);
		free(pr);
	}
}
