/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:10:12 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 19:59:05 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	get_token_len(char *input_at_i)
{
	size_t	i;
	char	quotes;

	i = 0;
	if (is_onstr(OPERATORS, input_at_i[i]))
	{
		if (input_at_i[i] == input_at_i[i + 1])
			return (2);
		return (1);
	}
	while (input_at_i[i]
		&& !is_spaces(input_at_i[i])
		&& !is_onstr(OPERATORS, input_at_i[i]))
	{
		if (is_onstr(QUOTES, input_at_i[i]))
		{
			quotes = input_at_i[i++];
			while (input_at_i[i] && input_at_i[i] != quotes)
				i++;
		}
		i++;
	}
	return (i);
}

size_t	get_nr_statements(char *input)
{
	size_t	count;
	bool	flag;
	bool	quotes;

	count = 0;
	flag = false;
	quotes = false;
	while (*input)
	{
		if (is_onstr(OPERATORS, *input))
			count++;
		if (is_onstr(QUOTES, *input) && *input == *(input + 1))
			input++;
		else if (is_onstr(QUOTES, *input))
			quotes = !quotes;
		if (*input != ' ' && !is_onstr(OPERATORS, *input) && !flag && !quotes)
		{
			flag = true;
			count++;
		}
		else if (*input == ' ' || is_onstr(OPERATORS, *input))
			flag = false;
		input++;
	}
	return (count);
}

char	**tokenizer(char *input)
{
	size_t		i;
	size_t		k;
	char		**token;
	size_t		len;
	size_t		j;

	i = 0;
	k = 0;
	token = malloc((get_nr_statements(input) + 1) * sizeof(char *));
	while (input[i])
	{
		len = get_token_len(&input[i]);
		if (!len)
		{
			i += 1;
			continue ;
		}
		token[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (input[i] && j < len)
			token[k][j++] = input[i++];
		token[k++][j] = '\0';
	}
	token[k] = NULL;
	return (token);
}
