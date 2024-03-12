/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:24:56 by kaan              #+#    #+#             */
/*   Updated: 2024/03/12 20:16:26 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//trying to start parser
void	grammar(t_token *tokens)
{
	if (tokens->type < 10 || tokens->type > 70)
		printf("%s: command not found\n", tokens->value);
	tokens = tokens->next;
}
