/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:38:33 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 16:37:52 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_cd(t_shell *shell, t_parser *parser)
{
	char	**token;

	token = parser->token;
	if (parser->token_count > 2)
	{
		ft_putendl_fd(CD_TOO_MANY_ARGS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		return (cd_util(token[1], shell));
}
