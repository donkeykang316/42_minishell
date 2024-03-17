/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defining_legacy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 15:27:44 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// this function loops through the tokenized linked list, and assigns values 
// to the node->type parameter, which identifies what time of string it holds
void	assignment(t_token **tokens)
{
	t_token	*current;

	current = (*tokens);
	if (tokens == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
		find_type(current);
		printf("%d\n", current->type);
		current = current->next;
	}
}

// finds the type of the string (operator, command, string [check parsing.h])
void	find_type(t_token *node)
{
	find_cmd(node);
	find_op(node);
	if (node->type == 0)
		node->type = T_WORD;
}

//compares the string with names of commands, if perfect comparison,
//then assigns corresponding value
int	find_cmd(t_token *node)
{
	if (!ft_memcmp_ms(node->value, "echo"))
		node->type = T_ECHO;
	else if (!ft_memcmp_ms(node->value, "cd"))
		node->type = T_CD;
	else if (!ft_memcmp_ms(node->value, "pwd"))
		node->type = T_PWD;
	else if (!ft_memcmp_ms(node->value, "export"))
		node->type = T_EXPORT;
	else if (!ft_memcmp_ms(node->value, "unset"))
		node->type = T_UNSET;
	else if (!ft_memcmp_ms(node->value, "env"))
		node->type = T_ENV;
	else if (!ft_memcmp_ms(node->value, "exit"))
		node->type = T_EXIT;
	if (node->type != 0)
		return (1);
	return (0);
}

// compares the string with operands, assigns them if identical

