/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:19 by mdomnik           #+#    #+#             */
/*   Updated: 2024/04/08 06:53:29 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_prompt *init_prompt(t_prompt *prompt)
{
	prompt = malloc(sizeof(t_prompt));
	prompt->envp = malloc(sizeof(t_envll)); 
	prompt->parser = malloc(sizeof(t_parser));
	prompt->lexer = NULL;
	prompt->printable = 0;
	prompt->word = NULL;
	return (prompt);
}

//duplicates a double pointer
char	**double_dup(char **str)
{
	int	i;
	char **ret;

	i = 0;
	while(str[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (!ret)
		return(NULL);
	i = 0;
	while(str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		if (ret[i] == NULL)
		{
			free_double(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

void free_double(char **double_str)
{
	if (double_str == NULL)
		return;

	int i = 0;
	while (double_str[i] != NULL)
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

//prints the entire stack (linked list)
void	print_lexer(t_prompt *prompt)
{
	t_lexer	*current;

	current = prompt->lexer;
	if (prompt->lexer == NULL)
		printf("Stack is empty\n");
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("word: [%s] ", current->word);
		printf("token: [%d] ", current->token);
		printf("index: [%d]\n", current->index);
		current = current->next;
	}
}

void	print_parser(t_prompt *prompt)
{
	t_parser	*current;
	int			i;

	i = 0;
	current = prompt->parser;
	if (prompt->parser == NULL)
		printf("Stack is empty\n");
	printf("parser contents:\n");
	while (current != NULL)
	{
		printf("cmd: [%s] ", current->cmd);
		printf("args: ");
		if (current->args != NULL && current->args[0] != NULL) {
			while (current->args[i] != NULL)
			{
				printf("[%s] ", current->args[i]);
				i++;
			}
		}
		printf("\n");
		printf("input: [%d] [%s]\n", current->input, current->i_str);
		printf("output: [%d] [%s]\n", current->output, current->o_str);
		i = 0;
		/*printf("files: ");
		if (current->files != NULL && current->files[0] != NULL) {
			while (current->files[i] != NULL)
			{
				printf("[%s] ", current->files[i]);
				i++;
			}
		}
		printf("\n");
		printf("index: %d\n", current->index);*/
		current = current->next;
	}
}