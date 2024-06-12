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

void    print_parser(t_parser *parser)
{
    printf("Token count:%d\n", parser->token_count);
    while (parser)
    {
        while (*(parser->token))
	    {
		    printf("%s ", *(parser->token));
            parser->token++;
	    }
        printf("\n");
        parser = parser->next;
    }
}
