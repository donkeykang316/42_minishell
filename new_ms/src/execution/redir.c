/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/16 13:41:45 by kaan             ###   ########.fr       */
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

void	ft_open(char *token, int option)
{
	if (open(token, O_WRONLY | option | O_CREAT, 0666) == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}
}

void	redir_output(t_parser *parser)
{
	close(STDOUT_FILENO);
	while (parser->next->operator == GREAT
		|| parser->next->operator == APPEND)
	{
		if (parser->operator == GREAT)
			ft_open(parser->next->token[0], O_TRUNC);
		else if (parser->operator == APPEND)
			ft_open(parser->next->token[0], O_APPEND);
		parser = parser->next;
		close(STDOUT_FILENO);
	}
	if (parser->operator == GREAT)
		ft_open(parser->next->token[0], O_TRUNC);
	else if (parser->operator == APPEND)
		ft_open(parser->next->token[0], O_APPEND);
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

bool	pipe_redir_check(t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	while (temp)
	{
		if (temp->operator != NONE)
			return (false);
		temp = temp->next;
	}
	return (true);
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
	if (!pipe_redir_check(parser) && fork() == 0)
		exec_cmd(shell, temp);
	else if (parser->operator == NONE)
		exec_cmd(shell, temp);
	else
		pipe_exe(shell, parser);
}
