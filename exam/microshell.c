#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void    ft_putstr_fd2(char *str, char *av)
{
    while (*str)
        write(2, str++, 1);
    if (av)
        while (*av)
            write(2, av++, 1);
    write(2, "\n", 1);
}

void    ft_execute(char **av, int i, int tmp_fd, char **env)
{
    av[i] = NULL;
    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);
    execve(av[0], av, env);
    ft_putstr_fd2("error: cannot execute", av[0]);
    exit(1);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd[2];
	int	tmp_fd;
    (void)ac;

    i = 0;
    tmp_fd = dup(STDIN_FILENO);
    while (av[i] && av[i + 1])
    {
        av = &av[i + 1];
        i = 0;
        while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
            i++;
        if (strcmp(av[0], "cd") == 0)
        {
            if (i != 2)
                ft_putstr_fd2("error: cd: bad arguments", NULL);
            else if (chdir(av[1]) != 0)
                ft_putstr_fd2("error: cd: cannot change directory to ", av[1]);
        }
        else if (i != 0 && (av[1] == NULL || strcmp(av[i], ";") == 0))
        {
            if (fork() == 0)
                ft_execute(av, i, tmp_fd, env);
            else
            {
                close(tmp_fd);
                while (waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                tmp_fd = dup(STDIN_FILENO);
            }
        }
        else if (i != 0 && strcmp(av[i], "|") == 0)
        {
            pipe(fd);
            if (fork() == 0)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                ft_execute(av, i, tmp_fd, env);
            }
            else
            {
                close(fd[1]);
                close(tmp_fd);
                tmp_fd = fd[0];
            }
        }
    }
    close(tmp_fd);
}
