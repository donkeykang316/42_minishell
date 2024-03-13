/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_uti_legacy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:57:04 by kaan              #+#    #+#             */
/*   Updated: 2024/03/13 15:39:39 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// frees the stack
void	ft_free(t_token **tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}

// duplicates string
char	*ft_strdup_ms(char *s1)
{
	char	*dest;
	size_t	i;

	dest = (char *) malloc(ft_strlen_ms(s1) + 1);
	i = 0;
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}



//prints the entire stack (linked list)
void	print_stack(t_token **token)
{
	t_token	*current;

	current = (*token);
	if (token == NULL)
	{
		printf("Stack is empty\n");
	}
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}
