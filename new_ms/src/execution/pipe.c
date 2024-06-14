/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:45:51 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 13:46:09 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	left_side(t_parser *parser, t_shell *shell, int pipe_fd[2])
{
	close(STDOUT_FILENO);
	dup(pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(shell, parser);
}

void	right_side(t_parser *parser, t_shell *shell, int pipe_fd[2])
{
	close(STDIN_FILENO);
	dup(pipe_fd[0]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_cmd(shell, parser);
}

void	pipe_exe(t_shell *shell, t_parser *parser)
{
	pid_t	child_pid;
	int		pipe_fd[2];
	int		status;

	parser->operator = NONE;
	if (pipe(pipe_fd) == -1)
		exit_shell(shell, PIPE_ERR, EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
		exit_shell(shell, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0)
		left_side(parser, shell, pipe_fd);
    right_side(parser->next, shell, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	exit_status = status / 256;
}
