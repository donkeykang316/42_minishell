/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:41:47 by kaan              #+#    #+#             */
/*   Updated: 2024/03/06 14:51:45 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	builtin_command(char *str, char *temp)
{
	if (!ft_memcmp(str, "echo ", 5))
		ft_echo(str);
	else if (!ft_memcmp(str, "pwd", 3))
		ft_pwd(str);
	else if (!ft_memcmp(str, "cd ", 3))
		ft_cd(str);
	else if (!ft_memcmp(str, "exit", 4))
		return (0);
	else
	{
		temp = ft_strjoin(str, ": command not found");
		printf("%s\n", temp);
		free(temp);
	}
	return (1);
}

int	main(void)
{
	char	*str;
	char	*temp;

	temp = NULL;
	while (1)
	{
		str = readline("[minishell]$ ");
		if (!str)
		{
			printf("readline error\n");
			break ;
		}
		add_history(str);
		if (!builtin_command(str, temp))
			break ;
	}
	free(str);
	return (0);
}
