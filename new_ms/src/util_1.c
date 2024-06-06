/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:37:31 by kaan              #+#    #+#             */
/*   Updated: 2024/06/06 17:53:07 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double(char **double_str)
{
	int	i;

	i = 0;
	if (double_str == NULL)
		return ;
	while (double_str[i] != NULL)
	{
		free(double_str[i]);
		i++;
	}
	free(double_str);
}

void	free_shell(t_shell *shell, int i)
{
	if (i == 1)
	{
		if (shell->env)
			free_double_pointer(shell->env);
		if (shell && shell->main_path)
			free(shell->main_path);
		rl_clear_history();
		free(shell);
	}
}

void	exit_shell(t_data *data, int exit_stat)
{
	if (shell)
		free_shell(shell, 1);
	exit(exit_stat);
}
