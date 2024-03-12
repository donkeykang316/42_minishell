/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:41:47 by kaan              #+#    #+#             */
/*   Updated: 2024/03/10 10:15:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_command(char *str, char *temp)
{
	char *catstr;
	
	catstr = str;
	while (*catstr == ' ')
		catstr++;
	if (!ft_memcmp(catstr, "echo ", 5))
		ft_echo(str);
	else if (!ft_memcmp(catstr, "pwd", 3))
		ft_pwd(str);
	else if (!ft_memcmp(catstr, "cd ", 3))
		ft_cd(str);
	else if (!ft_memcmp(catstr, "env", 3))
		ft_env(str);
	else if (!ft_memcmp(catstr, "exit", 4))
		return (0);
	else
	{
		temp = ft_strjoin(str, ": command not found");
		printf("%s\n", temp);
		free(temp);
	}
	return (1);
}


