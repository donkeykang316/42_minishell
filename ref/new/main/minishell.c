/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:40:56 by kaan              #+#    #+#             */
/*   Updated: 2024/03/17 11:21:48 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// main
int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	(void)argc; // ~~
	(void)argv; //throw error, when inputted
	(void)envp; //use to access environmental variables
	ms_loop(&prompt);
	return (0);
}

int ms_loop(t_prompt *prompt)
{
	prompt->lexer = NULL;
	prompt->parser = NULL;
	while (1)
	{
		prompt->line = readline(CL_NAME);
		split_cmd(prompt);
		// if (!prompt_lexing(&prompt))
		// 	error_seq(prompt, "lexing failed", 1);
		// if (!define_groups(&prompt))
		// 	error_seq(prompt, "parsing failed", 1);
		// print_lexer(&prompt);
		// print_parser(&prompt);
		// error_seq(prompt, "Finished", 0);
	}
	return (0);
}

// //prints the entire stack (linked list)
// void	print_lexer(t_global **global)
// {
// 	t_lexer	*current;

// 	current = (*global)->lexer;
// 	if ((*global)->lexer == NULL)
// 	{
// 		printf("Stack is empty\n");
// 	}
// 	printf("Stack contents:\n");
// 	while (current != NULL)
// 	{
// 		printf("word: [%s] ", current->word);
// 		printf("token: [%d] ", current->token);
// 		printf("index: [%d]\n", current->index);
// 		// printf("add: [%p]", current);
// 		// printf("next: [%p]\n", current->next);
// 		// printf("prev: [%p]\n", current->prev);
// 		current = current->next;
// 	}
// }

// void	print_parser(t_global **global)
// {
// 	t_parser	*current;

// 	current = (*global)->parser;
// 	if ((*global)->parser == NULL)
// 	{
// 		printf("Stack is empty\n");
// 	}
// 	printf("Stack contents:\n");
// 	while (current != NULL)
// 	{
// 		printf("cmd: [%s] ", current->cmd);
// 		// printf("content: [%s] ", current->content);
// 		// printf("redir: [%d] ", current->redirection);
// 		printf("index: [%d]\n", current->index);
// 		// printf("add: [%p]", current);
// 		// printf("next: [%p]\n", current->next);
// 		// printf("prev: [%p]\n", current->prev);
// 		current = current->next;
// 	}
// }

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
