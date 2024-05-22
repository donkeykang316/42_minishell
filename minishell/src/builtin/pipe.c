#include "../../inc/minishell.h"

void	cmd_count(t_shell *shell)
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
    shell->fd = malloc(sizeof(int) * (i - 1) * 2);
    n = 0;
    while (n != (i - 1) * 2)
    {
        shell->fd[n] = n + 3;
        n++;
    }
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

void    pip_exe(t_shell *shell, int *fd, int pid)
{
    if (!pid)
    {
        if (shell->parser->output == 1)
        {
            if (dup2(fd[0], 0) == -1)
            {
                perror("pipe error1\n");
                return ;
            }
            //execute(shell);
            //perror(shell->parser->args[0]);
            tmp_echo(shell);
            if (close(fd[0]) == -1)
                perror("pipe error2\n");
            if (close(fd[1]) == -1)
                perror("pipe error3\n");
            reset_loop(shell, NULL);
        }
    }
    if (shell->parser->output == 1)
    {
        if (/*dup2(fd[1], 1) == -1
            || */close(fd[0]) == -1
            || close(fd[1]) == -1)
        {
            perror("pipe error4\n");
            return ;
        }
        perror("why");
    }
    //reset_loop(shell, NULL);
}

void	pipex(t_shell *shell)
{
    int i = 0;

    cmd_count(shell);
    while (i != 10)
    {
        printf("fd:%d\n", shell->fd[i]);
        i++;
    }
    reset_loop(shell, NULL);
    /*int	*fd;
    int pid;

    
    while (shell->parser)
    {
        pid = fork();
        pip_exe(shell, fd, pid);
        shell->parser = shell->parser->next;
    }*/
}
