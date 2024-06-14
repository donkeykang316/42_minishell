/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:04:13 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 18:11:00 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	exit_path(char **paths, char *cmd, int exit_status_x)
{
	if (cmd)
		perror(cmd);
	free_d_lst(paths);
	if (!WIFSIGNALED(exit_status_x))
		exit_status = exit_status_x;
	exit(exit_status);
}

char	**get_paths(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (!strcmp_ms("PATH", temp->var_name))
	{
		temp = temp->next;
		if (temp == NULL)
			return (NULL);
	}
	return (ft_split(temp->var_value, ':'));
}

char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*tmp;
	char	*bin_path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin_path = ft_strjoin_ms(tmp, cmd);
		if (access(bin_path, F_OK | X_OK) == 0)
			return (bin_path);
		free(bin_path);
		i++;
	}
	return (NULL);
}

void	err_cmd(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	find_path(t_shell *shell, t_parser *parser)
{
	char		*bin_path;
	char		**paths;

	bin_path = parser->token[0];
	paths = get_paths(shell->envp_lst);
	bin_path = get_bin_path(parser->token[0], paths);
	if (!bin_path)
	{
		err_cmd(parser->token[0]);
		exit_path(paths, NULL, 127);
	}
	if (execve(bin_path, parser->token, shell->envp) == -1)
	{
		free(bin_path);
		exit_path(paths, parser->token[0], 127);
	}
	free(bin_path);
	exit_path(paths, NULL, EXIT_SUCCESS);
	return ;
}
