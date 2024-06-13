/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 17:16:15 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	single_export(t_shell *shell)
{
	t_envp	*envp;

	envp = shell->envp_lst;
	while (envp != NULL)
	{
		if (envp->is_exported)
			printf("declare -x %s=\"%s\"\n", envp->var_name, envp->var_value);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}

int	err_export_identifier(char *token)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	exp_export(char *token, t_shell *shell)
{
	t_envp	*envp;

	envp = shell->envp_lst;
	while (envp != NULL)
	{
		if (strcmp_ms(token, envp->var_name))
		{
			envp->is_exported = true;
			break ;
		}
		envp = envp->next;
	}
}

int	cmd_export(t_shell *shell, t_parser *parser)
{
	int			exit_status_x;
	size_t		i;

	if (parser->token_count == 1)
		return (single_export(shell));
	exit_status_x = EXIT_SUCCESS;
	i = 0;
	while (parser->token[++i])
	{
		if (!is_valid_id(parser->token[i]))
			exit_status_x = err_export_identifier(parser->token[i]);
		else if (is_onstr(parser->token[i], '='))
		{
			save_user_vars(parser->token[i], &shell->envp_lst, true);
			continue ;
		}
		else
			exp_export(parser->token[i], shell);
	}
	return (exit_status_x);
}
