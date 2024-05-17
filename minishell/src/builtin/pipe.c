#include "../../inc/minishell.h"

int	err(char *error)
{
	while (*error)
		write(2, error++, 1);
	return (1);
}

void	pip_exe(t_shell *shell)
{
	int	fd[2];
	int status;
    int pid;
    int pip_op;

    pip_op = shell->parser->output;
    if (pip_op && pipe(fd) == -1)
    {
        err("pipe error1\n");
        return ;
    }
    pid = fork();
    if (!pid)
    {
        if (pip_op &&
            (dup2(fd[1], 1) == -1
            || close(fd[0]) == -1
            || close(fd[1]) == -1))
            {
                err("pipe error2\n");
                return ;
            }
            find_path(shell);
    }
    waitpid(pid, &status, 0);
    if (pip_op &&
        (dup2(fd[0], 0) == -1
        || close(fd[0]) == -1
        || close(fd[1]) == -1))
        {
            err("pipe error3\n");
            return ;
        }
}

void	pipex(t_shell *shell)
{
    while (shell->parser)
    {
        if (shell->parser->output == 1)
            pip_exe(shell);
        else
            execute(shell);
        shell->parser = shell->parser->next;
    }
	reset_loop(shell, NULL);
}
