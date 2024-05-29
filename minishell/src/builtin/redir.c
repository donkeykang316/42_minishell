/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/05/29 15:15:59 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	great(t_shell *shell)
{
    int i;
    int pip_fd[0];
    
    i = 0;
    shell->fd = malloc(sizeof(int));
    while (cmp_str(shell->parser->files[i], shell->parser->o_str) != 0)
    {
	    *(shell->fd) = open(shell->parser->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	    if (*(shell->fd) == -1)
	    {
            perror("Open Error");
		    return ;
	    }
        close(*(shell->fd));
        i++;
    }
    if (cmp_str(shell->parser->files[i], shell->parser->o_str) == 0)
    {
        *(shell->fd) = open(shell->parser->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	    if (*(shell->fd) == -1)
	    {
            perror("Open Error");
		    return ;
	    }
    }
    shell->parser->output = -1;
    if (pipe(pip_fd) == -1)
        perror("red pipe error");
    shell->pid = fork();
    if (shell->pid == -1)
        perror("fork error");
    if (shell->pid == 0)
    {
        if (dup2(pip_fd[0], 0) == -1)
            perror("error1");
        if (dup2(*(shell->fd), 1) == -1)
            perror("error2");
        close(*(shell->fd));
        close(pip_fd[0]);
        close(pip_fd[1]);
        find_builtin(shell);
    }
    waitpid(-1, NULL, 0);
    close(*(shell->fd));
    close(pip_fd[0]);
    close(pip_fd[1]);
    reset_loop(shell, NULL);
}