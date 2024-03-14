/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 20:53:51 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"
#include "../../inc/lexer.h"

//ADD SPLITTING TOMORROW INTO PIPES
int split_commands(t_global **global)
{
	t_lexer	*lexer;

	lexer = (*global)->lexer;
	while(lexer->next != NULL)
	{
		if (lexer->token == T_PIPE)
		{
			
		}
		lexer->next
	}
}

//trims whitespace and when it finds a word it creates a node from it
int	prompt_lexing(t_global **global)
{
	t_lexer	*temp;
	int		i;
	int		x;
	
	i = 0;
	x = 0;
	temp = (*global)->lexer;
	(*global)->prompt = trim_whitespace((*global)->prompt);
	while ((*global)->prompt[i] != '\0')
	{	
		if(!is_whitespace_null((*global)->prompt[i]))
		{
			if(is_quote((*global)->prompt[i]))
				i += create_quote_node(global, i, (*global)->prompt[i], x);
			else
				i += create_node(global, i, x);
			x++;
		}
		if((*global)->prompt[i] == '\0')
			break;
		i++;
	}
	return (1);
}

//scans the future node word and checks if its a token, creates node
// accordingly
int create_node(t_global **global, int	i, int x)
{
	t_lexer	*new;
	char	*temp;
	int		j;

	j = 0;
	while(!is_whitespace_null((*global)->prompt[i + j]))
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
		new = lexernew_ms(temp, 0, x);
	else
		new = lexernew_ms(NULL, (check_token(temp)), x);
	lexeraddback_ms(&(*global)->lexer, new);
	free(temp);
	return (j);
}

int create_quote_node(t_global **global, int	i, char	c, int x)
{
	t_lexer	*new;
	char	*temp;
	int		j;

	i++;
	j = 0;
	while((*global)->prompt[i + j] != c &&
	 (*global)->prompt[i + j] != '\0')
		j++;
	if ((*global)->prompt[i + j] == '\0') //add actual error sequence
		error_seq((*global), "no closing quote\n", 1);
	temp = (char *)malloc((j + 1) * sizeof(char));
	j = 0;
	while((*global)->prompt[i + j] != c &&
		 (*global)->prompt[i + j] != '\0')
	{
		temp[j] = (*global)->prompt[i + j];
		j++;
	}
	temp[j] = '\0';
	if ((*global)->prompt[i + j] == '\0') //add actual error sequence
		error_seq((*global), "no closing quote\n", 1);
	if (finddollar_typecheck(temp, c))
		new = lexernew_ms(temp, T_REPLACE, x);
	else
		new = lexernew_ms(temp, T_WORD, x);
	lexeraddback_ms(&(*global)->lexer, new);
	free(temp);
	return (j + 2);
}

