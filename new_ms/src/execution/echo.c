/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:42:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 14:00:55 by kaan             ###   ########.fr       */
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
		if (!parser->token[i + 1] && parser->operator != LESS)
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cmd_echo(t_shell *shell)
{
	t_parser	*parser;
	bool		option_n;

	parser = shell->parser;
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
