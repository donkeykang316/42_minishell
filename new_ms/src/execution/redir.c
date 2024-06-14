/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 18:36:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less(t_parser *parser)
{
	int		fd;
	char	*err_msg;
	int		i;

	i = 0;
	printf("file_count:%d\n", parser->next->token_count);
	if (parser->next->token[0])
	{
		/*while (parser->next->operator == LESS)
			parser = parser->next;
		while (parser->next->operator == LESS)
			parser = parser->next;
		*/
		if (access(parser->next->token[0], F_OK) == 0)
		{
			fd = open(parser->next->token[0], O_RDONLY, 0666);
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			err_msg = ft_strjoin("minishell: ", parser->next->token[0]);
			perror(err_msg);
			free(err_msg);
			exit_status = 2;
			exit(EXIT_FAILURE);
		}
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
		exec_cmd(shell, temp);
	else
		pipe_exe(shell, parser);
}
