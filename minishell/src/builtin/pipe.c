/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:35:00 by kaan              #+#    #+#             */
/*   Updated: 2024/06/05 19:53:41 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_processes(t_shell *shell)
{
	int		status;
	int		save_stat;
	pid_t	pid;
	int		i;

	i = *(shell->cmd_count);
	save_stat = 0;
	while (i != 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				save_stat = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				save_stat = WTERMSIG(status);
		}
		else if (pid == -1)
		{
			perror("error1");
			proc_termination(shell, NULL, shell->parser->cmd);
		}
		else
		{
			printf("PID_eror2:%d\n", pid);
			reset_loop(shell, NULL, shell->parser->cmd);
		}
		i--;
	}
	*(shell->exit_status) = save_stat;
}

void	proc_termination(t_shell *shell, char *msg,
			char *cmd)
{
	if (msg)
		ft_perror(msg, cmd);
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
		if (shell->parser->index == 0 || shell->parser->index == 1)
			great(shell, 0);
		else
			great(shell, (shell->parser->index - 1) * 2);
	}
	else if (shell->parser->input == T_LESSER)
	{
		if (cmp_str(shell->parser->o_str, "STDOUT") == 0)
			less(shell, 1, -1);
		else if (cmp_str(shell->parser->o_str, "PIPE") == 0)
			less(shell, (shell->parser->index - 1) * 2, 0);
	}
	else if (shell->parser->input == T_HEREDOC)
	{
		if (shell->parser->index == 0 || shell->parser->index == 1)
			heredoc(shell, 1);
		else
			heredoc(shell, (shell->parser->index - 1) * 2);
	}
	else
		proc_termination(shell, NULL, shell->parser->cmd);
}

void	pipex(t_shell *shell)
{
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
	fd_close(shell);
	wait_processes(shell);
	reset_loop(shell, NULL, NULL);
}
