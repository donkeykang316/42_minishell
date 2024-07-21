#include "pipe_test.h"

int main(int a, char **av, char **env)
{
    int     fd;
    int     pip_fd[2];
    int     pid;
    char    *path = "/bin/ls";
    char    *cmd[] = {"ls", "-l", NULL};
    char    *file = "out";

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    printf("fd:%d\n", fd);
    if (pipe(pip_fd) == -1)
        perror("pipe error");
    pid = fork();
    if (pid == -1)
        perror("fork error");
    else if (pid == 0)
    {
        if (dup2(pip_fd[0], 0) == -1)
            perror("error1");
        if (dup2(fd, 1) == -1)
        perror("error3");
        close(fd);
        close(pip_fd[0]);
        close(pip_fd[1]);
        execve(path, cmd, env);
    }
    waitpid(-1, NULL, 0);
    close(fd);
    close(pip_fd[0]);
    close(pip_fd[1]);
}
