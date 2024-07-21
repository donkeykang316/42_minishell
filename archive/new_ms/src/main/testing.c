#include "../../inc/minishell.h"

void    print_envp(t_envp **envp)
{
    t_envp *head;

    head = *envp;
    printf("vlist:\n");
    while(head)
    {
        printf("%s", head->var_name);
        if (head->var_value)
            printf("  %s", head->var_value);
        printf("\n");
        head = head->next;
    }
}

void    print_parser(t_parser *test)
{

    t_parser    *parser;
    int i = 0;

    parser = test;
    write(2, "Token count: ", 13);
    ft_putnbr_fd(parser->token_count, 2);
    write(2, "\n", 1);
    while (parser)
    {
        i = 0;
        while (parser->token[i])
	    {
		    write(2, parser->token[i], ft_strlen(parser->token[i]));
            write(2, " ", 2);
            i++;
	    }
        if (parser->operator == NONE)
            ft_putendl_fd("\t[NONE]", 2);
        else if (parser->operator == PIPE)
            ft_putendl_fd("\t[PIPE]", 2);
        else if (parser->operator == LESS)
            ft_putendl_fd("\t[LESS]", 2);
        else if (parser->operator == HEREDOC)
            ft_putendl_fd("\t[HEREDOC]", 2);
        else if (parser->operator == GREAT)
            ft_putendl_fd("\t[GREAT]", 2);
        else if (parser->operator == APPEND)
           ft_putendl_fd("\t[APPEND]", 2);
        parser = parser->next;
    }
}

void    print_token(char **token)
{
    int i = 0;
    ft_putendl_fd("token: ", 2);
    while (token[i])
    {
        write(2, token[i], ft_strlen(token[i]));
        write(2, " ", 1);
        i++;
    }
    write(2, "\n", 1);
}
