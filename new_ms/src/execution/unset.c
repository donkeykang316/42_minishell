/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:11:10 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 16:42:18 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_util(t_parser *parser, t_envp **envp_list)
{
	int	i;

	i = 1;
	while (i < parser->token_count)
	{
		unset_var(parser->token[i], envp_list);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cmd_unset(t_shell *shell, t_parser *parser)
{
	if (parser->token_count == 1)
		return (EXIT_SUCCESS);
	return (unset_util(parser, &shell->envp_lst));
}
