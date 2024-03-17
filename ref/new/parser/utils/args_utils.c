/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:59:45 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 20:33:51 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_args	*argsnew_ms(char *content, int x)
{
	t_args		*element;

	element = (t_args *)malloc(sizeof(t_args));
	if (!element)
		return (NULL);
	element->content = ft_strdup(content);
	element->index = x;
	element->prev = NULL;
	element->next = NULL;
	return (element);
}

void	argsaddback_ms(t_args **lst, t_args *new)
{
	t_args		*temp;

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


t_args *argsfreelist_ms(t_args **lst)
{
	t_args *temp;

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