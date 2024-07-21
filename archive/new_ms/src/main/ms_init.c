/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:04:26 by kaan              #+#    #+#             */
/*   Updated: 2024/06/17 22:25:12 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp	*init_envp_lst(char **envp)
{
	t_envp	*head;
	t_envp	*temp;
	char	**line;
	size_t	i;

	line = split_envp(envp[0]);
	head = envp_new_node(line[0], line[1], true);
	free(line);
	i = 1;
	temp = head;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		temp->next = envp_new_node(line[0], line[1], true);
		free(line);
		temp = temp->next;
		i += 1;
	}
	init_oldpwd(&head);
	return (head);
}

void	shell_init(char **envp, t_shell *shell)
{
	shell->envp = envp;
	shell->envp_lst = init_envp_lst(envp);
	shell->parser = NULL;
	shell->more_redir_pipe = false;
	config_signals();
}
