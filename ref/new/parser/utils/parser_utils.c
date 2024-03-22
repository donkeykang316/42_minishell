/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:22:44 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 20:22:50 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//creates new node in the parser linked list
t_parser	*parsernew_ms(char *cmd, char *options, int redir, int x)
{
	t_parser		*element;
	t_args			*argument;
	t_redir			*redirection;

	element = (t_parser *)malloc(sizeof(t_parser));
	argument = (t_args *)malloc(sizeof(t_args));
    redirection = (t_redir *)malloc(sizeof(t_redir));
	if (!element)
		return (NULL);
	if (cmd)
		element->cmd = ft_strdup(cmd);
	else
		element->cmd = NULL;
	if (options)
		element->options = ft_strdup(options);
	else
		element->options = NULL;
	element->redir = redirection;
	element->args = argument;
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
		if ((*lst)->options)
			free((*lst)->options);
		free(*lst);
		*lst = temp;
	}
	argsfreelist_ms((*lst)->args);
	redirfreelist_ms((*lst)->redir);
	*lst = NULL;
	return (NULL);
}


