/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 18:35:33 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"
#include "../../inc/lexer.h"

//trims whitespace and when it finds a word it creates a node from it
int	prompt_lexing(t_global **global)
{
	t_lexer	*temp;
	int		i;
	
	i = 0;
	temp = (*global)->lexer;
	(*global)->prompt = trim_whitespace((*global)->prompt);
	while ((*global)->prompt[i] != '\0')
	{	
		if(!is_whitespace_null((*global)->prompt[i]))
			i += create_node(global, i);
		if((*global)->prompt[i] == '\0')
			break;
		i++;
	}
	return (1);
}

//scans the future node word and checks if its a token, creates node
// accordingly
int create_node(t_global **global, int	i)
{
	t_lexer	*new;
	char	*temp;
	int		j;

	j = 0;
	while(!is_whitespace((*global)->prompt[i + j]))
		j++;
	temp = (char *)malloc((j + 1) * sizeof(char));
	j = 0;
	while(!is_whitespace_null((*global)->prompt[i + j]))
	{
		temp[j] = (*global)->prompt[i + j];
		j++;
	}
	temp[j] = '\0';
	if(!check_token(temp))
		new = lexernew_ms(temp, 0);
	else
		new = lexernew_ms(NULL, (check_token(temp)));
	lexeraddback_ms(&(*global)->lexer, new);
	free(temp);
	return (j);
}

