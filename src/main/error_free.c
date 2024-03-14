/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:36:02 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 16:57:26 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void error_seq(t_global *global, char *error, int xit)
{
		lexerfreelist_ms(&(global)->lexer);
		parserfreelist_ms(&(global)->parser);
		free(global->prompt);
		global->prompt = NULL;
		printf("%s\n", error);
		if (xit == 1)
			exit(1);
}