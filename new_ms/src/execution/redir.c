/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/15 16:14:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less(t_parser *parser)
{
	int		fd;

	fd = 0;
	if (parser->next->token[0])
	{
		while (parser->next->operator == LESS)
		{
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile_exit();
			parser = parser->next;
		}
		while (parser->next->operator == LESS)
		{
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile_exit();
			parser = parser->next;
		}
		if (parser->next->token_count > 2
			&& parser->next->token[1])
			less_multi_file(parser, fd);
		else if (access(parser->next->token[0], F_OK) == 0)
			less_one_file(parser, fd);
		else
			less_invalid_input(parser->next->token[0]);
	}
}

void	heredoc(t_parser *parser)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (strcmp_ms(buff, parser->next->token[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	redir_output(t_parser *parser)
{
	close(STDOUT_FILENO);
	while (parser->next->operator == GREAT
		|| parser->next->operator == APPEND)
	{
		if (parser->operator == GREAT)
			open(parser->next->token[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (parser->operator == APPEND)
			open(parser->next->token[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		parser = parser->next;
		close(STDIN_FILENO);
	}
	if (parser->operator == GREAT)
		open(parser->next->token[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (parser->operator == APPEND)
		open(parser->next->token[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
}

t_parser	*pipe_check(t_parser *parser)
{
	while (parser)
	{
		if (parser->operator == PIPE)
			return (parser);
		parser = parser->next;
	}
	return (NULL);
}

void	redir_exe(t_shell *shell, t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	if (parser->operator == LESS)
		less(parser);
	else if (parser->operator == HEREDOC)
		heredoc(parser);
	else
		redir_output(parser);
	temp->operator = NONE;
	while (parser->operator != NONE && parser->operator != PIPE)
		parser = parser->next;
	if (parser->operator == NONE)
	{
		/*if (pipe_check(parser))
			pipe_exe(shell, parser);*/
		perror("error");
		exec_cmd(shell, temp);
	}
	else
		pipe_exe(shell, parser);
}
