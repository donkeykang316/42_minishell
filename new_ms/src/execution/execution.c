/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 14:57:54 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern long long	exit_status;

bool	builtin(t_shell *shell)
{
	if (strcmp_ms(shell->parser->token[0], "exit"))
		cmd_exit(shell);
	else if (strcmp_ms(shell->parser->token[0], "cd"))
		exit_status = cmd_cd(shell);
	else if (strcmp_ms(shell->parser->token[0], "env"))
		exit_status = cmd_env(shell);
	else if (strcmp_ms(shell->parser->token[0], "echo"))
		exit_status = cmd_echo(shell);
	else if (strcmp_ms(shell->parser->token[0], "pwd"))
		exit_status = cmd_pwd();
	else if (strcmp_ms(shell->parser->token[0], "unset"))
		exit_status = cmd_unset(shell);
	else if (strcmp_ms(shell->parser->token[0], "export"))
		exit_status = cmd_export(shell);
	else if (ft_strchr(shell->parser->token[0], '=')
		&& is_valid_id(shell->parser->token[0]))
		exit_status = save_user_vars(shell->parser->token[0],
				&shell->envp_lst, false);
	else
		return (false);
	return (true);
}

void	execution(t_shell *shell)
{
	if (parser_size(shell->parser) == 1)
	{
		if (!builtin(shell) && fork() == 0)
		{
			signal(SIGINT, child_signals);
		}
	}
}
