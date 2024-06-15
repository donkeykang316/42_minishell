/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:42:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/15 16:29:05 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_util(t_parser *parser, bool option)
{
	int		i;

	i = 1;
	if (option)
		i++;
	while (parser->token[i] && i != parser->token_count)
	{
		printf("%s", parser->token[i]);
		if (parser->token[i + 1])
			printf(" ");
		if (parser->next)
			printf(" ");
		if (!parser->token[i + 1] && parser->operator != LESS)
			break ;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cmd_echo(t_parser *parser)
{
	bool		option_n;

	option_n = false;
	if (parser->token_count >= 2)
		option_n = strcmp_ms(parser->token[1], "-n");
	echo_util(parser, option_n);
	parser = parser->next;
	while (parser != NULL && parser->token_count > 2)
	{
		echo_util(parser, false);
		if (parser->operator == PIPE)
			break ;
		parser = parser->next;
	}
	if (!option_n)
		printf("\n");
	return (EXIT_SUCCESS);
}
