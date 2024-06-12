/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:08:45 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 21:06:46 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*p_new_node(int token_count)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	new->token_count = token_count;
	new->token = malloc((token_count + 1) * sizeof(char *));
	new->operator = NONE;
	new->next = NULL;
	return (new);
}
