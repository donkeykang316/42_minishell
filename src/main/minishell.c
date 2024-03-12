/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:40:56 by kaan              #+#    #+#             */
/*   Updated: 2024/03/12 17:16:21 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// main
int	main(void)
{
	char	*str;
	t_token	*tokens;

	tokens = NULL;
	while (1)
	{
		str = readline("[minishell]$ ");
		tokenize(str, &tokens);
		assignment(&tokens);
		//print_stack(&tokens);
		grammar(tokens);
		ft_free(&tokens);
		free(str);
	}
	return (0);
}
