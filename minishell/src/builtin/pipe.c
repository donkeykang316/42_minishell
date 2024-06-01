#include "../../inc/minishell.h"

void cmd_count(t_shell *shell)
{
	t_parser	*current;
    int         fd;
	int			i;
    int         r;
    int         n;

	current = shell->parser;
    i = 0;
    shell->red_fd = malloc(sizeof(int));
    *(shell->red_fd) = -2;
	if (shell->parser == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
        if (current->i_str != NULL)
            i++;
        if (current->output == T_GREATER
            || current->output == T_APPEND)
        {
            r = 0;
            while (cmp_str(current->files[r], current->o_str) != 0)
            {
	            fd = open(current->files[r], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	            if (fd == -1)
	            {
                    perror("Open Error");
		            return ;
	            }
                close(fd);
                r++;
            }
            if (cmp_str(current->files[r], current->o_str) == 0)
            {
                if (current->file_types[r] == 2)
                    *(shell->red_fd) = open(current->files[r], O_WRONLY | O_CREAT | O_TRUNC, 0777);
                else if (current->file_types[r] == 5)
                {
                    *(shell->red_fd) = open(current->files[r], O_WRONLY | O_CREAT | O_APPEND, 0777);
                }
                if (*(shell->red_fd) == -1)
	            {
                    perror("Open Error");
		            return ;
	            }
            }
        }
        else if (current->input == T_LESSER)
        {
            *(shell->red_fd) = open(current->i_str, O_RDONLY);
            if (*(shell->red_fd) == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else if (current->input == T_HEREDOC)
            handle_here_document(shell);
		current = current->next;
	}
    shell->fd = malloc(sizeof(int) * i * 2);
    n = 0;
    while (n != i)
    {
        pipe(shell->fd + n * 2);
        n++;
    }
    shell->cmd_count = malloc(sizeof(int));
    *(shell->cmd_count) = i;
}

void    fd_close(t_shell *shell)
{
    int i;

    i = 0;
    if (*(shell->fd) != -2)
    {
        while (i != (*(shell->cmd_count) - 1) * 2)
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

void    pip_exe(t_shell *shell, int i, int j)
{
    if ((i == 1 && j == -1) 
        || (i == 0 && j == -1))
    {
        if (dup2(shell->fd[i], i) == -1)
            perror("error2");
    }
    else if (j == -1)
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
        i += 2;
    }
    else
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
        if (dup2(shell->fd[i + 3], 1) == -1)
            perror("error2");
    }
    fd_close(shell);
    //find_builtin(shell);
    find_path(shell);
    reset_loop(shell, NULL);
}

void pipex(t_shell *shell)
{
    int     status;
    int     i;

    i = 0;
    shell->pid = -2;
    cmd_count(shell);
    while (shell->parser)
    {
        shell->pid = fork();
        if (shell->pid == -1)
            perror("fork error");
        else if (shell->pid == 0)
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
                        reset_loop(shell, NULL);
                    }
                    else if (shell->parser->index == 0 || shell->parser->index == 1)
                        great(shell, 0);
                    else
                        great(shell, (shell->parser->index - 1) * 2);
                }
            else if (shell->parser->input == T_LESSER
                || shell->parser->input == T_HEREDOC)
                less(shell, 1);
            else
                reset_loop(shell, NULL);
            i++;
        }
        shell->parser = shell->parser->next;
    }
    waitpid(-1, &status, 0);
    fd_close(shell);
    reset_loop(shell, NULL);
}
