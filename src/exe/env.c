/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:42:08 by kaan              #+#    #+#             */
/*   Updated: 2024/04/16 06:47:50 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	ft_env(t_prompt *prompt)
{
	int	i;

	if (!ft_memcmp_ms(prompt->parser->cmd, "env"))
	{
		i = 0;
        while (prompt->envp->env[i])
        {
            printf("%s\n", prompt->envp->env[i]);
            i++;
        }
        
    }
}
