/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/03/05 16:10:54 by kaan             ###   ########.fr       */
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
	static char	*temp = NULL;
	int			i;

	if (str[ft_strlen(str) - 1] == c)
	{
		i = 0;
		while (str[i] != c)
			i++;
		pr = ft_substr(str, i + 1, ft_strlen(str) - 1);
		pr[ft_strlen(pr) - 1] = '\0';
		printf("%s\n", pr);
		return ;
	}
	else
	{
		i = 0;
		stemp = ft_strjoin(ft_substr(str, i, ft_strlen(str) - 1), "\n");
		while (1)
		{
			temp = ft_strjoin(readline("quote> "), "\n");
			stemp = ft_strjoin(stemp, temp);
			free(temp);
			if (stemp[ft_strlen(stemp) - 2] == c)
			{
				stemp[ft_strlen(stemp) - 1] = '\0';
				add_history(stemp);
				while (str[i] != c)
					i++;
				pr = ft_substr(stemp, i + 1, ft_strlen(stemp) - 2);
				pr[ft_strlen(pr) - 2] = '\0';
				printf("%s\n", pr);
				return ;
			}
		}
	}
}

void	ft_echo(const char *str)
{
	char	*pr;
	int		i;

	pr = NULL;
	if (ft_strchr(str, 34))
		quatation_case(str, 34, pr);
	else if (ft_strchr(str, 39))
		quatation_case(str, 39, pr);
	else
	{
		i = 5;
		while (str[i] == 32)
			i++;
		pr = ft_substr(str, i, ft_strlen(str));
		printf("%s\n", pr);
		free(pr);
	}
}
