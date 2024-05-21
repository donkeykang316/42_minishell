#include "../../inc/minishell.h"

void    tmp_echo(t_shell *shell)
{
    int i = 0;

    while (shell->parser->args[i])
    {
        printf("%s", shell->parser->args[i]);
        i++;
    }
}

void	pipex(t_shell *shell)
{
    int	fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe error1\n");
        return ;
    }
    while (shell->parser)
    {
        if (shell->parser->output == 1)
        {
            if (dup2(fd[0], 0) == -1
                || close(fd[0]) == -1
               || close(fd[1]) == -1)
                {
                    perror("pipe error2\n");
                    return ;
                }
                //execute(shell);
                //perror(shell->parser->args[0]);
                tmp_echo(shell);
                //reset_loop(shell, NULL);
        }
        else
        {
            if (dup2(fd[1], 1) == -1
                || close(fd[0]) == -1
                || close(fd[1]) == -1)
                {
                   perror("pipe error3\n");
                    return ;
                }
                perror("why");
                tmp_echo(shell);
                reset_loop(shell, NULL);
        }
        shell->parser = shell->parser->next;
    }
}
