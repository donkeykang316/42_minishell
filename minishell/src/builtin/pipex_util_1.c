/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:54:29 by kaan              #+#    #+#             */
/*   Updated: 2024/06/05 20:16:31 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	err_fd(t_shell *shell)
{
	perror("Open error");
	*(shell->exit_status) = 1;
	exit(EXIT_FAILURE);
}

void	err_fd_2(t_shell *shell)
{
	perror("");
	*(shell->exit_status) = 1;
	if (!shell->parser->next)
		reset_loop(shell, NULL, NULL);
	else
		*(shell->red_fd) = -2;
}

void	fd_close(t_shell *shell)
{
	int	i;

	i = 0;
	if (*(shell->fd) != -2)
	{
		while (i != *(shell->cmd_count) * 2)
		{
			if (close(shell->fd[i]) == -1)
				perror("fd close error");
			i++;
		}
	}
	if (*(shell->red_fd) != -2)
	{
		if (close(*(shell->red_fd)) == -1)
			perror("red_fd close error");
	}
}
