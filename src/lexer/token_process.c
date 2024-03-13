/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 14:47:55 by mdomnik          ###   ########.fr       */
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
		if (!is_whitespace((*global)->prompt[i]))
	}
	if ((*global)->prompt[i] == '\0')
	{
		printf("%d\n", i);
		return(1);
	}
	return (1);
}