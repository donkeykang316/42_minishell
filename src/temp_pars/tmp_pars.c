#include "../../inc/minishell.h"

void ms_loop(t_prompt *prompt)
{
	prompt->line = readline(CL_NAME);
	/*split_tokens(prompt);

	add_history(prompt->line);
	if (prompt->line != NULL)
		ms_loop(prompt);*/
}