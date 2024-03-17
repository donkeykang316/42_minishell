/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexical_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 11:06:32 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	tok_loop(char *str, t_lextmp *tp)
{
	while (!is_whitespace(str[tp->i + tp->j]) && str[tp->i + tp->j] != '\0')
		tp->j++;
	tp->data = malloc((tp->j + 1) * sizeof(char));
	tp->j = 0;
	while (!is_whitespace(str[tp->i]) && str[tp->i] != '\0')
	{
		tp->data[tp->j] = str[tp->i];
		tp->j++;
		tp->i++;
	}
	tp->data[tp->j] = '\0';
}

// skips whitespaces, and creates nodes from
// strings seperated by the whitespaces
void	tokenize(char *str, t_token **token)
{
	t_token	*temp;
	t_lextmp	tp;

	tp.i = 0;
	while (str[tp.i] != '\0')
	{
		tp.j = 0;
		if (!is_whitespace(str[tp.i]) && str[tp.i] != '\0')
		{
			tok_loop(str, &tp);
			temp = ft_lstnew_ms(tp.data);
			ft_lstadd_back_ms(token, temp);
			free(tp.data);
		}
		if (str[tp.i] == '\0')
			break ;
		tp.i++;
	}
}
