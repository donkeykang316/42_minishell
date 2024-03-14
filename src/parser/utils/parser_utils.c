/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:22:44 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 13:45:37 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//creates new node in the parser linked list
t_parser	*parsernew_ms(char *cmd, char *content, int redir, int x)
{
	t_parser		*element;

	element = (t_parser *)malloc(sizeof(t_parser));
	if (!element)
		return (NULL);
	if (cmd)
		element->cmd = ft_strdup(cmd);
	else
		element->cmd = NULL;
	if (content)
		element->content = content;
	else
		element->content = NULL;
	element->redirection = redir;
	element->index = x;
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

//adds new node to the back of the parser linked list
void	parseraddback_ms(t_parser **lst, t_parser *new)
{
	t_parser		*temp;

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

//frees the parser linked list
t_parser *parserfreelist_ms(t_parser **lst)
{
	t_parser *temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			free ((*lst)->cmd);
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}