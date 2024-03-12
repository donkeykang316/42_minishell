/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:24:56 by kaan              #+#    #+#             */
/*   Updated: 2024/03/12 17:51:43 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//trying to start parser
void	grammar(t_token *tokens)
{
	while (tokens)
	{
		printf("grammar:%s\n", tokens->value);
		tokens = tokens->next;
	}
}
