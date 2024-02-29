/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/02/29 01:04:15 by kaan             ###   ########.fr       */
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
	char	*sec_str;
	int		len;

	if (str[ft_strlen(str) - 1] == c)
	{
		len = ft_strlen(str);
		pr = ft_memchr(str, str[6], len - 1);
		pr[ft_strlen(pr) - 1] = '\0';
		printf("%s\n", pr);
	}
	/*else
	{
		
	}*/
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
