/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:24 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/17 17:17:37 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void split_tokens(t_prompt *prompt)
{
	t_lexer	*lexer;
	int		i;

	i = 0;
	lexer = prompt->lexer;
	prompt->line = trim_whitespace(prompt->line);
	printf("%s\n", prompt->line);
	while(prompt->line[i] != '\0')
	{
		if(!is_whitespace_null(prompt->line[i]))
			i += node_process(prompt, i);
		i++;
	}
}

int	node_process(t_prompt *prompt, int	i)
{
	t_lexer *new;
	char	*str;

	while (prompt->line[i] != '\0')
	{
		if(is_quote(prompt->line[i]))
		{
			str = quote_process(prompt, str, i, is_quote(prompt->line[i]));
			i += ft_strlen()
		}	
		if(prompt->line[i] != '\0')
			i++;
	}
}

char *quote_process(t_prompt *prompt, int i, int qtype)
{
	
}