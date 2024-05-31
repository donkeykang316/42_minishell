/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/05/31 19:30:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    less(t_shell *shell, int i)
{
    if (shell->parser->index != 0)
    {
        if (dup2(shell->fd[i], 1) == -1)
            perror("great error1");
    }
    if (dup2(*(shell->red_fd), 0) == -1)
        perror("great error2");
    fd_close(shell);
    find_path(shell);
    reset_loop(shell, NULL);
}

void	great(t_shell *shell, int i)
{
    if (dup2(shell->fd[i], 0) == -1)
        perror("great error1");
    if (dup2(*(shell->red_fd), 1) == -1)
        perror("great error2");
    fd_close(shell);
    find_path(shell);
    reset_loop(shell, NULL);
}