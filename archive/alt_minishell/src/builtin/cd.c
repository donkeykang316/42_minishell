/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:17:43 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/05 18:56:23 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Changes the current working directory.
 * 
 * @param shell The shell structure.
 */
void	builtin_cd(t_shell *shell)
{
	if (count_args(shell->parser->args) > 1)
	{
		*(shell->exit_status) = 1;
		reset_loop(shell, ERR_CDARG, shell->parser->cmd);
		return ;
	}
	else if (count_args(shell->parser->args) == 0)
	{
		cd_home(shell);
		return ;
	}
	else if (cmp_str(shell->parser->args[0], "-") == 0)
	{
		change_last_dir(shell);
		reset_loop(shell, NULL, shell->parser->cmd);
		return ;
	}
	set_last_dir(shell);
	if (chdir(shell->parser->args[0]) == -1)
	{
		printf("minishell: cd: %s:", shell->parser->args[0]);
		*(shell->exit_status) = 1;
		reset_loop(shell, ERR_CD, shell->parser->cmd);
		return ;
	}
}

void	cd_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv("HOME", shell->env);
	if (!home)
	{
		reset_loop(shell, ERR_CDHOME, shell->parser->cmd);
		return ;
	}
	if (chdir(home) == -1)
	{
		free(home);
		reset_loop(shell, ERR_CD, shell->parser->cmd);
		return ;
	}
	free(home);
	reset_loop(shell, NULL, shell->parser->cmd);
}

void	set_last_dir(t_shell *shell)
{
	if (shell->last_dir)
		free(shell->last_dir);
	shell->last_dir = getcwd(NULL, 0);
}

void	change_last_dir(t_shell *shell)
{
	char	*temp;

	printf("%s\n", shell->last_dir);
	temp = getcwd(NULL, 0);
	chdir(shell->last_dir);
	free(shell->last_dir);
	shell->last_dir = ft_strdup(temp);
	free(temp);
}
