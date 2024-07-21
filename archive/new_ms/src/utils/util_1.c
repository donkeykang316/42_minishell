/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:00:23 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 18:24:07 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	envp_clean(t_envp **list)
{
	t_envp	*temp;
	t_envp	*next_node;

	if (!list)
		return ;
	temp = *list;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = next_node;
	}
	*list = NULL;
}

void	parser_clean(t_parser **parser)
{
	t_parser	*temp;
	t_parser	*next_node;

	if (!parser)
		return ;
	temp = *parser;
	while (temp != NULL)
	{
		next_node = temp->next;
		free_d_lst(temp->token);
		free(temp);
		temp = next_node;
	}
	*parser = NULL;
}

void	destroy(t_shell *shell)
{
	rl_clear_history();
	if (shell->envp_lst)
		envp_clean(&shell->envp_lst);
	if (shell->parser)
		parser_clean(&shell->parser);
}

void	exit_shell(t_shell *shell, char *msg, int exit_status)
{
	(void)shell;
	if (shell)
		destroy(shell);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

bool	strcmp_ms(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((s1 && !s2) || (!s1 && s2))
		return (false);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (true);
	return (false);
}
