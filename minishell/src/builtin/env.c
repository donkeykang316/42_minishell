/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:38:32 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/05 18:51:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the environment variables stored in the shell.
 *
 * @param shell The shell structure containing the environment variables.
 */
void	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->parser->args[0])
	{
		*(shell->exit_status) = 1;
		reset_loop(shell, ERR_CD, shell->parser->cmd);
		return ;
	}
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}
