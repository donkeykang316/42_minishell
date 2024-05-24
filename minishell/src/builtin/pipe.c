#include "../../inc/minishell.h"

void cmd_count(t_shell *shell)
{
	t_parser	*current;
	int			i;
    int         n;

	current = shell->parser;
    i = 0;
	if (shell->parser == NULL)
		printf("Stack is empty\n");
	while (current != NULL)
	{
        if (current->cmd)
            i++;	
		current = current->next;
	}
    shell->fd = malloc(sizeof(int) * i * 2);
    n = 0;
    while (n != i)
    {
        pipe(shell->fd + n * 2);
        n++;
    }
    shell->cmd_count = &i;
}

void    tmp_echo(t_shell *shell)
{
    int i = 0;

    while (shell->parser->args[i])
    {
        printf("%s", shell->parser->args[i]);
        i++;
    }
}

void    fd_close(t_shell *shell)
{
    int i;

    i = 0;
    while (i != *(shell->cmd_count) * 2)
    {
        if (close(shell->fd[i]) == -1)
            perror("close error");
        i++;
    }
}

void    pip_exe(t_shell *shell, int i)
{
    /*pid = fork();
    if (pid == 0)
    {
        printf("i:%d\n", i);
        if (i != 1)
        {
            if (dup2(shell->fd[i], 0) == -1)
                perror("error2");
        }
        if (i != *(shell->cmd_count) * 2 - 1 && i != 1)
        {
            if (dup2(shell->fd[i + 3], 1) == -1)
                perror("error2");
        }
        else
        {
            if (dup2(shell->fd[i], 1) == -1)
                perror("error2");
        }
        fd_close(shell);
        find_path(shell);
    }*/
    if (i == 0)
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
    }
    if (i == 1)
    {
        if (dup2(shell->fd[i], 1) == -1)
            perror("error2");
    }
    fd_close(shell);
    find_path(shell);
    reset_loop(shell, NULL);
}

void	pipex(t_shell *shell)
{
    int pid;
    int i;

    cmd_count(shell);
    i = 0;
    while (shell->parser)
    {
        pid = fork();
        if (pid == 0)
        {
            if (cmp_str(shell->parser->i_str, "STDIN") == 0
                && cmp_str(shell->parser->o_str, "PIPE") == 0)
                pip_exe(shell, 1);
            else if (cmp_str(shell->parser->i_str, "PIPE") == 0
                    && cmp_str(shell->parser->o_str, "STDOUT") == 0)
                    pip_exe(shell, 0);
        }
        shell->parser = shell->parser->next;
    }
    fd_close(shell);
    reset_loop(shell, NULL);
}
