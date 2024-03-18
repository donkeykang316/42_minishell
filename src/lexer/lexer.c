/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/18 16:45:22 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//splits prompt into tokens and nodes of the lexer linked list
void split_tokens(t_prompt *prompt)
{
	t_lexer	*lexer;
	int		i;
	char	*temp;

	i = 0;
	lexer = prompt->lexer;
	prompt->line = trim_whitespace(prompt->line);
	while(prompt->line[i] != '\0')
	{
		if(!is_whitespace_null(prompt->line[i]))
		{
			temp = NULL;
			i = node_process(prompt, i, temp);
		}
		if(prompt->line[i] != '\0')
				i++;
	}
}

int	node_process(t_prompt *prompt, int	i, char *temp)
{
	int		q;

	while (!is_whitespace_null(prompt->line[i]))
	{ 
		if (is_quote(prompt->line[i]))
		{
			q = is_quote(prompt->line[i++]);
			while(prompt->line[i] != q && prompt->line[i] != '\0')
				temp = append_char(temp, prompt->line[i++]);
			if(prompt->line[i] == '\0')
				simple_err(ERR_QUOTE);
			i++;
		}
		else 
			while(!is_quote(prompt->line[i]) && !is_whitespace_null(prompt->line[i]))
				temp = append_char(temp, prompt->line[i++]);
	}
	printf("%s\n", temp);
	return(i);
}

// char *quote_process(t_prompt *prompt, int i, int qtype)
// {
	
// }