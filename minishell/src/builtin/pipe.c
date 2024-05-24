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
    shell->cmd_count = malloc(sizeof(int));
    *(shell->cmd_count) = i;
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

/*static int	wait_processes(t_shell *shell)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	save_status = 0;
	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == shell->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}*/

void    pip_exe(t_shell *shell, int i, int j)
{
    if ((i == 1 && j == -1) 
        || (i == 0 && j == -1))
    {
        if (dup2(shell->fd[i], i) == -1)
            perror("error2");
    }
    else if (/*i !=0 && i != 1 && */j == -1)
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
    }
    else
    {
        if (dup2(shell->fd[i], 0) == -1)
            perror("error2");
        if (dup2(shell->fd[i + 3], 1) == -1)
            perror("error2");
    }
    fd_close(shell);
    find_path(shell);
    reset_loop(shell, NULL);
}

void	pipex(t_shell *shell)
{
    int i;
    int status;
    int pid;

    cmd_count(shell);

    i = 0;
    //print_parser(shell);
    while (shell->parser)
    {
        pid = fork();
        if (pid == 0)
        {
            if (cmp_str(shell->parser->i_str, "STDIN") == 0
                    && cmp_str(shell->parser->o_str, "PIPE") == 0)
                    pip_exe(shell, 1, -1);
            if (*(shell->cmd_count) == 2)
            {
                if (cmp_str(shell->parser->i_str, "PIPE") == 0
                        && cmp_str(shell->parser->o_str, "STDOUT") == 0)
                        {
                            pip_exe(shell, 0, -1);
                        }
            }
            else
            {
                if (cmp_str(shell->parser->i_str, "PIPE") == 0
                        && cmp_str(shell->parser->o_str, "STDOUT") == 0)
                        pip_exe(shell, *(shell->cmd_count) + 1, -1);
                else
                {
                    pip_exe(shell, i, 0);
                    i += 2;
                }
            }
        }
        shell->parser = shell->parser->next;
    }
    //wait_processes(shell);
    waitpid(shell->pid, &status, 0);
    fd_close(shell);
    reset_loop(shell, NULL);
}
