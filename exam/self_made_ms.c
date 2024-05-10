#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
    int i;

    i = 0;
    av[i] = NULL;
    i++;
    while (av[i])
        i++;
    av[i] = NULL;
    i = 1;
    execve(av[i], av, env);
}
