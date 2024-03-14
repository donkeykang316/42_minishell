/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:16:25 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 17:52:43 by mdomnik          ###   ########.fr       */
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
				delete_node_at_index(&lexer, lexer->index);
				delete_node_at_index(&lexer, lexer->next->index);
			}
			else
				error_seq(*global, "2 tokens in a row", 1);
			x++;
		}
		lexer = lexer->next;
	}
	join_cmd(global);
	return(1);
}

void join_cmd(t_global **global)
{
	t_lexer		*lexer;
	t_parser	*parse;
	int			seq;
	char		*args;
	char		*temp;
	char		*cmd;

	lexer = (*global)->lexer;
	seq = lexer->index;
	while(lexer->next != NULL)
	{
		if(lexer->index != seq)
			error_seq(*global, "cmd not sequential", 1);
		else if(lexer == (*global)->lexer)
			cmd = ft_strdup(lexer->word);
		else
		{
			temp = ft_strjoin(args, lexer->word);
			args = ft_strdup(temp);
			free(temp);
		}
		seq++;
		lexer = lexer->next;
	}
	parse = parsernew_ms(cmd, args, 0, seq);
	parseraddback_ms(&(*global)->parser, parse);
}