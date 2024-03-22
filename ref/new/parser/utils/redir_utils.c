/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:59:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 20:30:57 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_redir	*redirnew_ms(char *content, int redir)
{
	t_redir		*element;

	element = (t_redir *)malloc(sizeof(t_redir));
	if (!element)
		return (NULL);
	element->content = ft_strdup(content);
	element->redirection = redir;
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

void	rediraddback_ms(t_redir **lst, t_redir *new)
{
	t_redir		*temp;

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

t_redir *redirfreelist_ms(t_redir **lst)
{
	t_redir *temp;

	temp = *lst;
	if (!(*lst))
		return (NULL);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			free ((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (NULL);
}