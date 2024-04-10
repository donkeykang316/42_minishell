/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:10:56 by kaan              #+#    #+#             */
/*   Updated: 2024/04/10 10:49:10 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	ft_echo(t_prompt *prompt)
{
	int	i;

	if (!ft_memcmp_ms(prompt->parser->cmd, "echo"))
	{
		i = 0;
		if (!prompt->parser->args[i])
		{
			printf("\n");
			return ;
		}
		if (!ft_memcmp_ms(prompt->parser->args[i], "-n"))
			i++;
		while (prompt->parser->args[i])
		{
			if (!prompt->parser->args[i + 1])
			{
				if (!ft_memcmp_ms(prompt->parser->args[0], "-n"))
					printf("%s",prompt->parser->args[i]);
				else
					printf("%s\n",prompt->parser->args[i]);
			}
			else
				printf("%s ",prompt->parser->args[i]);
			i++;
		}
	}
}
