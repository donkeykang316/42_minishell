#include "../../inc/minishell.h"

int	err(char *error)
{
	while (*error)
		write(2, error++, 1);
	return (1);
}

void    child_proc(t_shell *shell, int *pip_fd)
{
    dup(STDIN_FILENO);
    dup2(pip_fd[1], STDOUT_FILENO);
    close(pip_fd[0]);
    find_builtin(shell);
}

void    main_proc(t_shell *shell, int *pip_fd)
{
    shell->parser = shell->parser->next;
    dup(STDOUT_FILENO);
    dup2(pip_fd[0], 0);
    close(pip_fd[1]);
    find_builtin(shell);
}

void	pipex(t_shell *shell)
{
    int fd[2];
    int pid;

    if (pipe(fd) == -1)
        err("pipe error");
    pid = fork();
    if (pid == -1)
        err("fork error");
    if (!pid)
        child_proc(shell, fd);
    else
        main_proc(shell, fd);
}
