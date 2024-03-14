/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:16:25 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 16:43:27 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//start by grouping all redirections with the following strings, if strings are (nil) error
//join them in parser, reduce until all left is cmd and inputs

int	define_groups(t_global **global)
{
 	t_lexer		*lexer;
	t_parser	*parse;
	int			x;

	x = 0;
	lexer = (*global)->lexer;
	while(lexer->next != NULL)
	{
		if (lexer->token > 0 && lexer->token < 6)
		{
			if (lexer->next->word != NULL)
			{
				parse = parsernew_ms(NULL, lexer->next->word, lexer->token, x);
				parseraddback_ms(&(*global)->parser, parse);
			}
			else
				error_seq(*global, "2 tokens in a row", 1);
			x++;
		}
		lexer = lexer->next;
	}
	return(1);
}