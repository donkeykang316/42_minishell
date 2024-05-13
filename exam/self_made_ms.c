#include <string.h>
#include <unistd.h>
#include <stdio.h>

void    execute(char **av, int i, char **env)
{
    av[i] = NULL;
    execve(av[0], av, env);
}

int	main(int ac, char **av, char **env)
{
    int i;
    int n = 0;

    i = 0;
    while (av[i] && av[i + 1])
    {
        av = &av[i + 1];
        while (av[i] && strcmp(av[i], ";"))
			    i++;
        if (fork())
            execute(av, i, env);
    }
}
