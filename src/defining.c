/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defining.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/10 16:02:14 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void assignment(t_token **tokens)
{
	t_token	*current;
	current = (*tokens);
	if (tokens == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
		
		current = current->next;
	}
}