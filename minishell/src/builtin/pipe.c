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

void    pip_exe(t_shell *shell)
{
    int pid;

    pid = fork();
    printf("pid: %d\n", pid);
    if (!pid)
    {
        if (cmp_str(shell->parser->i_str, "PIPE") == 0)
        {
            if (dup2(shell->fd[1], 1) == -1)
            {
                perror("pipe error1\n");
                return ;
            }
            //execute(shell);
            //perror(shell->parser->args[0]);
            tmp_echo(shell);
            if (close(shell->fd[0]) == -1)
                perror("pipe error2\n");
            if (close(shell->fd[1]) == -1)
                perror("pipe error3\n");
            if (close(shell->fd[2]) == -1)
                perror("pipe error4\n");
            if (close(shell->fd[3]) == -1)
                perror("pipe error5\n");
            //reset_loop(shell, NULL);
        }
    }
    if (cmp_str(shell->parser->o_str, "PIPE") == 0)
    {
        if (dup2(shell->fd[0], 0) == -1)
        {
            perror("pipe error4\n");
            return ;
        }
        if (close(shell->fd[0]) == -1)
            perror("pipe error6\n");
        if (close(shell->fd[1]) == -1)
            perror("pipe error7\n");
        if (close(shell->fd[2]) == -1)
            perror("pipe error8\n");
        if (close(shell->fd[3]) == -1)
            perror("pipe error9\n");
        perror("why");
    }
    //reset_loop(shell, NULL);
}

void	pipex(t_shell *shell)
{
    /*int i = 0;
    print_parser(parser);
    cmd_count(shell);
    while (i != 11)
    {
        printf("%d\n", shell->fd[i]);
        i++;
    }
    if (shell->fd)
        free(shell->fd);
    reset_loop(shell, NULL);*/
    cmd_count(shell);
    while (shell->parser)
    {
        pip_exe(shell);
        shell->parser = shell->parser->next;
    }
}
