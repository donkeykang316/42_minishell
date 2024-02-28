/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/02/28 23:19:15 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(const char *echo)
{
	char	*str;
	char	*pr;

	str = readline(echo);
	if (str)
	{
		if (!ft_memcmp(str, "echo ", 5))
		{
			pr = ft_substr(str, 5, ft_strlen(str));
			printf("%s\n", pr);
			free(pr);
		}
	}
	else
		printf("readline error\n");
	free(str);
}
