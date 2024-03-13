/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 15:44:38 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"
#include "../../inc/lexer.h"

int	prompt_lexing(t_global **global)
{
	t_lexer	*temp;
	int		i;
	
	i = 0;
	temp = (*global)->lexer;
	(*global)->prompt = trim_whitespace((*global)->prompt);
	while ((*global)->prompt[i] != '\0')
	{	
		if(!is_whitespace((*global)->prompt[i]))
			i += create_node(global, i);
		i++;
	}
	return (1);
}

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
	while(!is_whitespace((*global)->prompt[i + j]))
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
	return (j);
}

