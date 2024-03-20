/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:01:19 by kaan              #+#    #+#             */
/*   Updated: 2024/03/20 16:12:51 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

char	*main_proc(char *str)
{
	str = readline("msh% ");
	if (!str)
		ft_exit("readline error\n");
	return (str);
}

void	child_proc(char *str)
{
	printf("child:%s\n", str);
	free(str);
}

void	shell_loop(void)
{
	char	*str;
	int		pid;
	int		status;

	str = NULL;
	pid = fork();
	if (pid == -1)
		ft_exit("Fork error\n");
	while (1)
	{
		if (!pid)
		{
			child_proc(str);
		}
		str = main_proc(str);
		wait(&status);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	if (ac != 1)
		ft_exit("Excute the program without argument\n");
	shell_loop();
}
