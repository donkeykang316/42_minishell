/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:54:24 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 19:32:37 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long long	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	t_parser	*parser;
	char		*input;

	if (av && ac > 1)
		exit_shell(NULL, CL_ARGUMENTS_ERR, EXIT_FAILURE);
	shell_init(envp, &shell, &parser);
	while (1)
	{
		input = readline(CL_NAME);
		if (!valid_input(input, &shell))
			continue ;
		input = expanding(input, &shell);
		add_history(input);
		parser = parsing(input);
		shell.parser = parsing(input);
		//print_parser(shell.parser);
		exection(parser, &shell);
	}
	return (EXIT_SUCCESS);
}
