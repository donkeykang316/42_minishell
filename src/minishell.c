/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:41:47 by kaan              #+#    #+#             */
/*   Updated: 2024/02/29 01:23:07 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("");
		if (str)
		{
			if (!ft_memcmp(str, "echo ", 5))
				ft_echo(str);
			else if (!ft_memcmp(str, "exit", 4))
				break ;
			free(str);
		}
		else
		{
			printf("readline error\n");
			break ;
		}
	}
}
