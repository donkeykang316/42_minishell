/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:33:36 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 17:58:48 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern long long	exit_status;

bool	is_valid_id(char *token)
{
	size_t	i;

	i = 0;
	if (strcmp_ms(token, "="))
		return (false);
	while (token[i] && token[i] != '=')
	{
		if (ft_isdigit(token[i]) || token[i] == '!' || token[i] == '@'
			|| token[i] == '{' || token[i] == '}' || token[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

bool	builtin(t_shell *shell, t_parser *parser)
{
	if (strcmp_ms(parser->token[0], "exit"))
		cmd_exit(shell, parser);
	else if (strcmp_ms(parser->token[0], "cd"))
		exit_status = cmd_cd(shell, parser);
	else if (strcmp_ms(parser->token[0], "env"))
		exit_status = cmd_env(shell);
	else if (strcmp_ms(parser->token[0], "echo"))
		exit_status = cmd_echo(parser);
	else if (strcmp_ms(parser->token[0], "pwd"))
		exit_status = cmd_pwd();
	else if (strcmp_ms(parser->token[0], "unset"))
		exit_status = cmd_unset(shell, parser);
	else if (strcmp_ms(parser->token[0], "export"))
		exit_status = cmd_export(shell, parser);
	else if (ft_strchr(parser->token[0], '=')
		&& is_valid_id(parser->token[0]))
		exit_status = save_user_vars(parser->token[0],
				&shell->envp_lst, false);
	else
		return (false);
	return (true);
}

void	single_exe(t_shell *shell, t_parser *parser)
{
	if (builtin(shell, parser))
		return ;
	find_path(shell, parser);
}

void	exec_cmd(t_shell *shell, t_parser *parser)
{
	signal(SIGINT, child_signals);
	if (parser->operator == PIPE)
		pipe_exe(shell, parser);
	else if (parser->operator == NONE)
		single_exe(shell, parser);
	else
		redir_exe(shell, parser);
	exit(exit_status);
}

void	execution(t_shell *shell)
{
	t_parser	*parser;
	int			status;

	parser = shell->parser;
	if (parser_size(parser) == 1)
	{
		if (!builtin(shell, parser) && fork() == 0)
		{
			signal(SIGINT, child_signals);
			single_exe(shell, parser);
		}
	}
	else if (fork() == 0)
		exec_cmd(shell, parser);
	waitpid(-1, &status, 0);
	if (!WTERMSIG(status))
		exit_status = status / 256;
}
