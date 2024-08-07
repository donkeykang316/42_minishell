/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:09:53 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 15:08:34 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	exit_non_numeric_arg(void)
{
	exit_status = 2;
	ft_putendl_fd(EXIT_NON_NUMERIC_ARG, STDERR_FILENO);
}

void	cmd_exit(t_shell *shell, t_parser *parser)
{
	char	**token;

	token = parser->token;
	if (parser->token_count == 2 && ft_isnum(token[1]))
		exit_status = ft_atoi(token[1]);
	else if (parser->token_count == 2 && !ft_isnum(token[1]))
	{
		exit_status = 2;
		ft_putendl_fd(EXIT_NON_NUMERIC_ARG, STDERR_FILENO);
	}
	else if (parser->token_count > 2)
	{
		exit_status = EXIT_FAILURE;
		ft_putendl_fd(EXIT_TOO_MANY_ARGS, STDERR_FILENO);
	}
	else
		exit_status = EXIT_SUCCESS;
	if (shell)
		destroy(shell);
	exit(exit_status);
}
