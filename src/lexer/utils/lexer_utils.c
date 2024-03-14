/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:17 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 11:41:06 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//creates a new node in the lexer linked list
t_lexer	*lexernew_ms(char *word, int token, int x)
{
	t_lexer		*element;

	element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!element)
		return (NULL);
	if (word)
		element->word = ft_strdup(word);
	else
		element->word = NULL;
	element->token = token;
	element->index = x;
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

//adds new node to the back of the lexer linked list
void	lexeraddback_ms(t_lexer **lst, t_lexer *new)
{
	t_lexer		*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;	
}

//frees the lexer linked list
t_lexer *lexerfreelist_ms(t_lexer **lst)
{
	t_lexer *temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->word)
			free ((*lst)->word);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}