/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:23:31 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/18 16:14:24 by mdomnik          ###   ########.fr       */
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
	ms_loop(prompt);
	return (1);
}

//core loop of the shell
void ms_loop(t_prompt *prompt)
{
	prompt->line = readline(CL_NAME);
	split_tokens(prompt);
	
	add_history(prompt->line);
	if (prompt->line != NULL)
		ms_loop(prompt);
}