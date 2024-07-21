#include "pipe_test.h"

int main(int ac, char **av, char** env)
{
    char    *path1 = "/bin/ls";
    char    *cmd1[] = {"ls", "-l", NULL};
    char    *path2 = "/bin/cat";
    char    *cmd2[] = {"cat", "-e", NULL};
    int    fd[2];
    int     pid1;
    int     pid2;
    int     status;

    if (pipe(fd) == -1)
        perror("error1");
    pid1 = fork();
    if (pid1 == 0)
    {
        if (dup2(fd[1], 1) == -1)
            perror("error2");
        if (close(fd[0]) == -1
            && close(fd[1]) == -1)
            perror("error9");
        execve(path1, cmd1, env);
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            if (dup2(fd[0], 0) == -1)
                perror("error8");
            if (close(fd[0]) == -1
                && close(fd[1]) == -1)
                perror("error9");
            execve(path2, cmd2, env);
        }
    }
    if (close(fd[0]) == -1
        && close(fd[1]) == -1)
        perror("error9");
}