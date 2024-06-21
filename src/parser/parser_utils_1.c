/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:56:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 18:14:52 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void remove_redir_nodes(t_shell *shell, t_expand *expand)
{
	t_expand	*temp;

	temp = expand;
	while (expand->next != NULL && expand->token != T_PIPE)
	{
		if (expand->token == T_PIPE)
			break ;
		if (expand->token != T_WORD && expand->token != T_PIPE)
		{
			expand = remove_current_node(expand);
			expand = remove_current_node(expand);
		}
		else
			expand = expand->next;
	}
	shell->expand = temp;
}

void remove_pipe_and_prev(t_shell *shell, t_expand *expand)
{
	while(expand != NULL && expand->token != T_PIPE)
	{
		expand = remove_current_node(expand);
	}
	if (expand->token == T_PIPE)
		expand = remove_current_node(expand);
	shell->expand = expand;
}