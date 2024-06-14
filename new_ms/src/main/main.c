/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:54:24 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 17:35:01 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_status = 0;

void	final_clean(t_shell *shell)
{
	parser_clean(&shell->parser);
	shell->parser = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;
	char		*input;

	if (av && ac > 1)
		exit_shell(NULL, CL_ARGUMENTS_ERR, EXIT_FAILURE);
	shell_init(envp, &shell);
	while (1)
	{
		input = readline(CL_NAME);
		if (!valid_input(input, &shell))
			continue ;
		input = expanding(input, &shell);
		add_history(input);
		shell.parser = parsing(input);
		execution(&shell);
		final_clean(&shell);
	}
	return (EXIT_SUCCESS);
}
