/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:23:31 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/17 12:36:13 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// main
int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	int			i;

	i = 0;
	prompt = NULL;
	prompt = init_prompt(prompt);
	if(argc != 1 || argv[1])
		simple_err(ERR_I);
	prompt->envp->env = double_dup(envp);
	if (!prompt->envp->env)
		simple_err(ERR_ENV);
	while (prompt->envp->env[i] != NULL)
	{
		printf("%s\n", prompt->envp->env[i]);
		i++;
	}
	// ms_loop(&prompt);
	return (0);
}

// int ms_loop(t_prompt *prompt)
// {
// 	prompt->lexer = NULL;
// 	prompt->parser = NULL;
// 	while (1)
// 	{
// 		prompt->line = readline(CL_NAME);
// 		split_cmd(prompt);
// 		// if (!prompt_lexing(&prompt))
// 		// 	error_seq(prompt, "lexing failed", 1);
// 		// if (!define_groups(&prompt))
// 		// 	error_seq(prompt, "parsing failed", 1);
// 		// print_lexer(&prompt);
// 		// print_parser(&prompt);
// 		// error_seq(prompt, "Finished", 0);
// 	}
// 	return (0);
// }