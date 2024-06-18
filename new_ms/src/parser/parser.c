/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:39:22 by kaan              #+#    #+#             */
/*   Updated: 2024/06/17 21:17:37 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_operator	get_operator(char *operator)
{
	t_operator	op;

	if (!operator)
		op = NONE;
	else if (strcmp_ms(operator, "|"))
		op = PIPE;
	else if (strcmp_ms(operator, ">>"))
		op = APPEND;
	else if (strcmp_ms(operator, ">"))
		op = GREAT;
	else if (strcmp_ms(operator, "<<"))
		op = HEREDOC;
	else if (strcmp_ms(operator, "<"))
		op = LESS;
	else
		op = NONE;
	free(operator);
	return (op);
}

int	get_token_count(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

size_t	remove_quotes_size(char	*token)
{
	size_t	i;
	size_t	size;
	char	quotes;

	i = 0;
	size = 0;
	while (token[i])
	{
		while (token[i] && !is_onstr(QUOTES, token[i]))
		{
			i += 1;
			size += 1;
		}
		if (!token[i])
			break ;
		quotes = token[i++];
		while (token[i] && token[i] != quotes)
		{
			i += 1;
			size += 1;
		}
		quotes = 0;
	}
	return (size);
}

char	*remove_quotes(char	*token)
{
	size_t	i;
	size_t	j;
	char	quotes;
	char	*unquoted_token;

	i = 0;
	j = 0;
	quotes = '\0';
	unquoted_token = malloc((remove_quotes_size(token) + 1) * sizeof(char));
	while (token[i])
	{
		while (token[i] && !is_onstr(QUOTES, token[i]))
			unquoted_token[j++] = token[i++];
		if (!token[i])
			break ;
		quotes = token[i];
		i += 1;
		while (token[i] && token[i] != quotes)
			unquoted_token[j++] = token[i++];
		quotes = '\0';
	}
	unquoted_token[j] = '\0';
	free(token);
	return (unquoted_token);
}

t_parser	*parsing(char *input)
{
	char		**tokens;
	t_parser	*temp;
	t_parser	*head;
	size_t		idx[2];

	tokens = tokenizer(input);
	free(input);
	temp = p_new_node(get_token_count(&tokens[0]));
	head = temp;
	idx[0] = 0;
	while (tokens[idx[0]])
	{
		idx[1] = 0;
		while (tokens[idx[0]] && !is_onstr(OPERATORS, tokens[idx[0]][0]))
			temp->token[idx[1]++] = remove_quotes(tokens[idx[0]++]);
		temp->token[idx[1]] = NULL;
		if (!tokens[idx[0]])
			break ;
		temp->operator = get_operator(tokens[idx[0]++]);
		temp->next = p_new_node(get_token_count(&tokens[idx[1]]));
		temp = temp->next;
	}
	return (head);
}
