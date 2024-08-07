/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:50:38 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 20:59:33 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	get_exported_state(char *var_name, t_envp **envp)
{
	t_envp	*temp;

	temp = *envp;
	while (temp != NULL)
	{
		if (strcmp_ms(var_name, temp->var_name))
			return (temp->is_exported);
		temp = temp->next;
	}
	return (false);
}

char	**split_envp(char *envp)
{
	char	**splitted;
	size_t	equal;

	splitted = malloc(3 * sizeof(char *));
	equal = ft_strchr(envp, '=') - envp;
	splitted[0] = ft_substr(envp, 0, equal);
	splitted[1] = ft_substr(envp, equal + 1,
			ft_strlen(&envp[equal]));
	splitted[2] = NULL;
	return (splitted);
}

int	save_user_vars(char *statement, t_envp **envp, bool to_export)
{
	char	**line;

	line = split_envp(statement);
	if (get_exported_state(line[0], envp) && !to_export)
		to_export = true;
	unset_var(line[0], envp);
	envp_add_back(envp, envp_new_node(line[0], line[1], to_export));
	free(line);
	return (EXIT_SUCCESS);
}

void	init_oldpwd(t_envp **envp)
{
	char	*temp;

	unset_var("OLDPWD", envp);
	temp = ft_strjoin("OLDPWD=", getenv("HOME"));
	save_user_vars(temp, envp, true);
	free(temp);
}
