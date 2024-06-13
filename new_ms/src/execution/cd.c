/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:38:33 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 13:06:04 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_cd(t_shell *shell)
{
	char	**token;

	token = shell->parser->token;
	if (shell->parser->token_count > 2)
	{
		ft_putendl_fd(CD_TOO_MANY_ARGS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		return (cd_util(token[1], shell));
}
