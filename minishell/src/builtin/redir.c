/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:00:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/01 16:32:08 by kaan             ###   ########.fr       */
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
    single_cmd_exe(shell);
    /*find_path(shell);
    reset_loop(shell, NULL);*/
}

void	great(t_shell *shell, int i)
{
    if (dup2(shell->fd[i], 0) == -1)
        perror("great error1");
    if (dup2(*(shell->red_fd), 1) == -1)
        perror("great error2");
    fd_close(shell);
    single_cmd_exe(shell);
    /*find_path(shell);
    reset_loop(shell, NULL);*/
}

void handle_here_document(t_shell *shell)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    line = NULL;
    len = 0;
    *(shell->red_fd) = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (*(shell->red_fd) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("heredoc> ");
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        if (strncmp(line, shell->parser->i_str, strlen(shell->parser->i_str)) == 0
            && line[strlen(shell->parser->i_str)] == '\n') {
            break;
        }
        write(*(shell->red_fd), line, read);
        printf("heredoc> ");
    }
    free(line);
    close(*(shell->red_fd));
    *(shell->red_fd) = open("/tmp/heredoc_tmp", O_RDONLY);
    if (*(shell->red_fd) == -1) {
        perror("open temp file for read");
        exit(EXIT_FAILURE);
    }
}
