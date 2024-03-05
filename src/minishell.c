/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:41:47 by kaan              #+#    #+#             */
/*   Updated: 2024/03/05 16:17:32 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("[minishell]$ ");
		add_history(str);
		if (str)
		{
			if (!ft_memcmp(str, "echo ", 5))
				ft_echo(str);
			else if (!ft_memcmp(str, "exit", 4))
				break ;
			else
				printf("%s\n", ft_strjoin(str, ": command not found"));
		}
		else
		{
			printf("readline error\n");
			break ;
		}
	}
	free(str);
	return (0);
}
