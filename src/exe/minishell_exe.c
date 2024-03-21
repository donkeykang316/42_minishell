/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:01:19 by kaan              #+#    #+#             */
/*   Updated: 2024/03/21 20:12:54 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	handle_ctrlc(int sig)
{
	(void)sig;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	int		pid;
	int		status;

	(void)ac;
	(void)av;
	(void)env;
	if (ac != 1)
		ft_exit("Excute the program without argument\n");
	while (1)
	{
		str = readline(CL_NAME);
		pid = fork();
		if (pid == -1)
			ft_exit("Fork error\n");
		if (!pid)
		{
			printf("child:%s\n", str);
			signal(SIGINT, handle_ctrlc);
		}
		else
		{
			waitpid(pid, &status, 0);
			printf("Parent:%s\n", str);
		}
	}
}
