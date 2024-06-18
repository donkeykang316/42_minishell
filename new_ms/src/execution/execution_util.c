/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:08:26 by kaan              #+#    #+#             */
/*   Updated: 2024/06/18 14:08:46 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	redir_check(t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	while (temp->next && temp->operator == NONE)
		temp = temp->next;
	if (temp->operator != NONE && temp->operator != PIPE)
		return (true);
	return (false);
}

bool	pipe_check(t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	while (temp->next && temp->operator == NONE)
		temp = temp->next;
	if (temp->operator == PIPE)
		return (true);
	return (false);
}
