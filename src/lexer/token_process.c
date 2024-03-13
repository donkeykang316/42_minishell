/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:26 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 13:24:58 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	prompt_lexing(t_global **global)
{
	t_lexer	*temp;
	int		i;
	
	i = 0;
	(void **)global;
	temp = (*global)->lexer;
	while ((*global)->prompt[i] != EOF)
	{
		printf("%d\n", i);	
	}
}