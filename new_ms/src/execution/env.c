/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:39:27 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 13:41:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_env(t_shell *shell)
{
	t_envp	*temp;

	temp = shell->envp_lst;
	while (temp != NULL)
	{
		if (temp->is_exported)
			printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
