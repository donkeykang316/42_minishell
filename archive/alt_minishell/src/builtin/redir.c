/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/05 20:19:01 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pip_exe(t_shell *shell, int i, int j)
{
	if ((i == 1 && j == -1) 
		|| (i == 0 && j == -1))
	{
		if (dup2(shell->fd[i], i) == -1)
			perror("error2");
	}
	else if (j == -1)
	{
		if (dup2(shell->fd[i], STDIN_FILENO) == -1)
			perror("error2");
		i += 2;
	}
	else
	{
		if (dup2(shell->fd[i], STDIN_FILENO) == -1)
			perror("error2");
		if (dup2(shell->fd[i + 3], STDOUT_FILENO) == -1)
			perror("error2");
	}
	fd_close(shell);
	find_builtin_pipe(shell);
}

void	less(t_shell *shell, int i, int j)
{
	if (j == 0)
	{
		if (dup2(shell->fd[i + 3], STDOUT_FILENO) == -1)
			perror("great error1");
	}
	if (*(shell->red_fd) != -2)
	{
		if (dup2(*(shell->red_fd), STDIN_FILENO) == -1)
			perror("great error2");
	}
	fd_close(shell);
	find_builtin_pipe(shell);
}

void	great(t_shell *shell, int i)
{
	if (cmp_str(shell->parser->i_str, "PIPE") == 0
		&& shell->parser->cmd == NULL)
	{
		fd_close(shell);
		reset_loop(shell, NULL, shell->parser->cmd);
	}
	if (dup2(shell->fd[i], STDIN_FILENO) == -1)
		perror("great error1");
	if (dup2(*(shell->red_fd), STDOUT_FILENO) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin_pipe(shell);
}

void	heredoc(t_shell *shell, int i)
{
	char	*line;

	set_signals_child();
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (strcmp_ms(line, shell->parser->i_str) == 0)
			break ;
		write(*(shell->red_fd), line, ft_strlen(line));
		write(*(shell->red_fd), "\n", 1);
		free(line);
	}
	close(*(shell->red_fd));
	shell->red_fd = malloc(sizeof(int));
	*(shell->red_fd) = open("/tmp/heredoc_tmp", O_RDONLY);
	if (*(shell->red_fd) == -1)
		err_fd(shell);
	if (shell->parser->index != 0)
	{
		if (dup2(shell->fd[i], STDOUT_FILENO) == -1)
			perror("great error1");
	}
	if (dup2(*(shell->red_fd), STDIN_FILENO) == -1)
		perror("great error2");
	fd_close(shell);
	find_builtin_pipe(shell);
}

void	handle_here_document(t_shell *shell)
{
	*(shell->red_fd) = open("/tmp/heredoc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*(shell->red_fd) == -1)
		err_fd(shell);
}
