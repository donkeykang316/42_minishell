/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:13:30 by kaan              #+#    #+#             */
/*   Updated: 2024/06/06 18:09:37 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *ft_getcwd(void)
{
    char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
        return (NULL);
    return (pwd);
}

int	init_env(t_shell *shell, char **envp)
{
	int		i;

	shell->envp = ft_calloc(get_env_size(envp) + 1, sizeof * data->envp);
	if (!data->envp)
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_shell	*init_shell(t_shell *shell, char **env)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
    if (init_env(shell, env))
		exit_shell(shell, EXIT_FAILURE);
    shell->line = NULL;
	shell->expand = NULL;
	shell->lexer = NULL;
    shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
    shell->cwd = ft_getcwd();
    shell->pid = 0;
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	shell = NULL;
    if (argc != 1 || argv[1])
		exit_shell(shell, EXIT_FAILURE);
	shell = init_shell(shell);
    if (shell == NULL)
		exit_shell(shell, EXIT_FAILURE);
    back_end(shell);
    front_end(shell);

}
