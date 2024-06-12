/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 21:11:54 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern long long	exit_status;

bool	builtin(t_shell *shell)
{
	if (strcmp_ms(shell->parser->token[0], "exit"))
		cmd_exit(shell);
	else
		return (false);
	return (true);
}

void	execution(t_shell *shell)
{
	//int		temp_status;

	if (parser_size(shell->parser) == 1)
	{
		if (!builtin(shell) && fork() == 0)
		{
			signal(SIGINT, child_signals);
			//exec_executables(parser, shell);
		}
	}
}