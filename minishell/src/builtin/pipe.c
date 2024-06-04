/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:35:00 by kaan              #+#    #+#             */
/*   Updated: 2024/06/04 17:17:19 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_processes(t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		remaining_children;

	remaining_children = 1;
	if (*(shell->cmd_count) != -1)
		remaining_children = *(shell->cmd_count);
	while (remaining_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status);
			remaining_children--;
		}
		else
			reset_loop(shell, NULL);
	}
}

void	proc_termination(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	if (shell->lexer)
		lexerfreelist_ms(&shell->lexer);
	if (shell->expand)
		expandfreelist_ms(&shell->expand);
	if (shell->parser)
		parserfreelist_ms(&shell->parser);
	if (shell->cmd_count)
		free(shell->cmd_count);
	shell->expand = NULL;
	shell->lexer = NULL;
	shell->parser = NULL;
	shell->cmd_count = NULL;
	reset_increment_k(0);
	exit(EXIT_SUCCESS);
}

void	child_proc(t_shell *shell)
{
	if (cmp_str(shell->parser->i_str, "STDIN") == 0
		&& cmp_str(shell->parser->o_str, "PIPE") == 0)
		pip_exe(shell, 1, -1);
	else if (cmp_str(shell->parser->i_str, "PIPE") == 0
		&& cmp_str(shell->parser->o_str, "STDOUT") == 0)
		pip_exe(shell, (shell->parser->index - 1) * 2, -1);
	else if (cmp_str(shell->parser->i_str, "PIPE") == 0
		&& cmp_str(shell->parser->o_str, "PIPE") == 0)
		pip_exe(shell, (shell->parser->index - 1) * 2, 0);
	else if (shell->parser->output == T_GREATER
		|| shell->parser->output == T_APPEND)
	{
		if (cmp_str(shell->parser->i_str, "PIPE") == 0
			&& shell->parser->cmd == NULL)
		{
			fd_close(shell);
			reset_loop(shell, "command not found here");
		}
		else if (shell->parser->index == 0 || shell->parser->index == 1)
			great(shell, 0);
		else
			great(shell, (shell->parser->index - 1) * 2);
	}
	else if (shell->parser->input == T_LESSER)
		less(shell, 1);
	else if (shell->parser->input == T_HEREDOC)
		heredoc(shell);
	else
		proc_termination(shell);
}

void	pipex(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	cmd_count(shell);
	while (shell->parser)
	{
		shell->pid = fork();
		if (shell->pid == -1)
			perror("fork error");
		else if (shell->pid == 0)
		{
			child_proc(shell);
			i++;
		}
		shell->parser = shell->parser->next;
	}
	waitpid(-1, &status, 0);
	//wait_processes(shell);
	fd_close(shell);
	reset_loop(shell, NULL);
}
