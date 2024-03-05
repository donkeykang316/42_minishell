/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:41:47 by kaan              #+#    #+#             */
/*   Updated: 2024/03/05 17:31:51 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*str;
	char	*temp;

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
			{
				temp = ft_strjoin(str, ": command not found");
				printf("%s\n", temp);
				free(temp);
			}
			free(str);
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
