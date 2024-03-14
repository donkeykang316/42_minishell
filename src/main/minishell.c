/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:40:56 by kaan              #+#    #+#             */
/*   Updated: 2024/03/14 16:44:01 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// main
int	main(int argc, char **argv, char **envp)
{
	t_global	global;
	(void)argc; // ~~
	(void)argv; //throw error, when inputted
	(void)envp; //use to access environmental variables
	ms_loop(&global);
	return (0);
}

int ms_loop(t_global *global)
{
	global->lexer = NULL;
	global->parser = NULL;
	while (1)
	{
		global->prompt = readline(CL_NAME);
		if (!prompt_lexing(&global))
			error_seq(global, "lexing failed", 1);
		if (!define_groups(&global))
			error_seq(global, "parsing failed", 1);
		error_seq(global, "Finished", 0);
		print_parser(&global);
	}
	return (0);
}

//prints the entire stack (linked list)
void	print_lexer(t_global **global)
{
	t_lexer	*current;

	current = (*global)->lexer;
	if ((*global)->lexer == NULL)
	{
		printf("Stack is empty\n");
	}
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("index: [%d]\n", current->index);
		// printf("add: [%p]", current);
		// printf("next: [%p]\n", current->next);
		// printf("prev: [%p]\n", current->prev);
		current = current->next;
	}
}

void	print_parser(t_global **global)
{
	t_parser	*current;

	current = (*global)->parser;
	if ((*global)->parser == NULL)
	{
		printf("Stack is empty\n");
	}
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("cmd: [%s] ", current->cmd);
		printf("content: [%s] ", current->content);
		printf("redir: [%d] ", current->redirection);
		printf("index: [%d]\n", current->index);
		// printf("add: [%p]", current);
		// printf("next: [%p]\n", current->next);
		// printf("prev: [%p]\n", current->prev);
		current = current->next;
	}
}

// int ms_loop(t_util *utils, t_token *tokens)
// {
	// char	*temp;
	// 
	// utils->args = readline(CL_NAME);
	// temp = ft_strtrim(utils->args, " ");
	// free(utils->args);
	// utils->args = temp;
	// add_history(utils->args);
	// tokenize(utils->args, &tokens);
	// assignment(&tokens);
	// print_stack(&tokens);
	//ft_free(&tokens);
	// free(utils->args);
	// return(1);
// }
