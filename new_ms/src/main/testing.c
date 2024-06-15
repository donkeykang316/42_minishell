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
    printf("Token count:%d\n", parser->token_count);
    while (parser)
    {
        i = 0;
        while (parser->token[i])
	    {
		    printf("%s ", parser->token[i]);
            i++;
	    }
        if (parser->operator == NONE)
            printf("\t[NONE]");
        else if (parser->operator == PIPE)
            printf("\t[PIPE]");
        else if (parser->operator == LESS)
            printf("\t[LESS]");
        else if (parser->operator == HEREDOC)
            printf("\t[HEREDOC]");
        else if (parser->operator == GREAT)
            printf("\t[GREAT]");
        else if (parser->operator == APPEND)
            printf("\t[APPEND]");
        printf("\n");
        parser = parser->next;
    }
}
