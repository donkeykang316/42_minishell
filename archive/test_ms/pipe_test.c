#include "pipe_test.h"

int main(int ac, char **av, char** env)
{
    char    *path1 = "/bin/ls";
    char    *cmd1[] = {"ls", "-l", NULL};
    char    *path2 = "/bin/cat";
    char    *cmd2[] = {"cat",NULL};
    char    *path3 = "/bin/echo";
    char    *cmd3[] = {"echo", "12345", NULL};
    char    *path4 = "/bin/cat";
    char    *cmd4[] = {"cat", NULL};
    char    *path5 = "/bin/cat";
    char    *cmd5[] = {"cat", "-e", NULL};
    int    fd[8];
    int     pid1;
    int     pid2;
    int     pid3;
    int     pid4;
    int     pid5;
    int     status;

    if (pipe(fd) == -1)
        perror("error1");
    if (pipe(fd + 2) == -1)
        perror("error1.5");
    if (pipe(fd + 4) == -1)
        perror("error1.5.5");
    if (pipe(fd + 6) == -1)
        perror("error2.5.5");
    pid1 = fork();
    if (pid1 == 0)
    {
        if (dup2(fd[1], 1) == -1)
            perror("error2");
        if (close(fd[0]) == -1)
            perror("error3");
        if (close(fd[1]) == -1)
            perror("error4");
        if (close(fd[2]) == -1)
            perror("error5");
        if (close(fd[3]) == -1)
            perror("error6");
        if (close(fd[4]) == -1)
            perror("error6");
        if (close(fd[5]) == -1)
            perror("error6");
        if (close(fd[6]) == -1)
            perror("error6");
        if (close(fd[7]) == -1)
            perror("error6");
        execve(path1, cmd1, env);
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            if (dup2(fd[0], 0) == -1)
                perror("error8");
            if (dup2(fd[3], 1) == -1)
                perror("error8");
            if (close(fd[0]) == -1)
                perror("error9");
            if (close(fd[1]) == -1)
                perror("error7");
            if (close(fd[2]) == -1)
                perror("error10");
            if (close(fd[3]) == -1)
                perror("error11");
            if (close(fd[4]) == -1)
                perror("error6");
            if (close(fd[5]) == -1)
                perror("error6");
            if (close(fd[6]) == -1)
                perror("error6");
            if (close(fd[7]) == -1)
                perror("error6");
            execve(path2, cmd2, env);
        }
        else
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                if (dup2(fd[2], 0) == -1)
                    perror("error8");
                if (dup2(fd[5], 1) == -1)
                    perror("error8");
                if (close(fd[0]) == -1)
                    perror("error9");
                if (close(fd[1]) == -1)
                    perror("error7");
                if (close(fd[2]) == -1)
                    perror("error10");
                if (close(fd[3]) == -1)
                    perror("error11");
                if (close(fd[4]) == -1)
                    perror("error6");
                if (close(fd[5]) == -1)
                    perror("error6");
                if (close(fd[6]) == -1)
                    perror("error6");
                if (close(fd[7]) == -1)
                    perror("error6");
                execve(path3, cmd3, env);
            }
            else
            {
                pid4 = fork();
                if (pid4 == 0)
                {
                    if (dup2(fd[4], 0) == -1)
                        perror("error8");
                    if (dup2(fd[7], 1) == -1)
                        perror("error8");
                    if (close(fd[0]) == -1)
                        perror("error9");
                    if (close(fd[1]) == -1)
                        perror("error7");
                    if (close(fd[2]) == -1)
                        perror("error10");
                    if (close(fd[3]) == -1)
                        perror("error11");
                    if (close(fd[4]) == -1)
                        perror("error6");
                    if (close(fd[5]) == -1)
                        perror("error6");
                    if (close(fd[6]) == -1)
                        perror("error6");
                    if (close(fd[7]) == -1)
                        perror("error6");
                    execve(path4, cmd4, env);
                }
                else
                {
                    pid5 = fork();
                    if (pid5 == 0)
                    {
                        if (dup2(fd[6], 0) == -1)
                            perror("error8");
                        if (close(fd[0]) == -1)
                            perror("error9");
                        if (close(fd[1]) == -1)
                            perror("error7");
                        if (close(fd[2]) == -1)
                            perror("error10");
                        if (close(fd[3]) == -1)
                            perror("error11");
                        if (close(fd[4]) == -1)
                            perror("error6");
                        if (close(fd[5]) == -1)
                            perror("error6");
                        if (close(fd[6]) == -1)
                            perror("error6");
                        if (close(fd[7]) == -1)
                            perror("error6");
                        execve(path5, cmd5, env);
                    }
                }
            }
        }
    
    }
    if (close(fd[0]) == -1)
        perror("error9");
    if (close(fd[1]) == -1)
        perror("error7");
    if (close(fd[2]) == -1)
        perror("error10");
    if (close(fd[3]) == -1)
        perror("error11");
    if (close(fd[4]) == -1)
        perror("error6");
    if (close(fd[5]) == -1)
        perror("error6");
    if (close(fd[6]) == -1)
        perror("error6");
    if (close(fd[7]) == -1)
        perror("error6");
}
