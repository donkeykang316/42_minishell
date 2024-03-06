/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:13:46 by kaan              #+#    #+#             */
/*   Updated: 2024/03/06 10:14:15 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo_init(t_echo *var)
{
	var->pr = NULL;
	var->temp1 = NULL;
	var->temp2 = NULL;
	var->i = 0;
}

void	free_echo(t_echo *var)
{
	if (var->pr)
		free(var->pr);
	if (var->temp1)
		free(var->temp1);
	if (var->temp2)
		free(var->temp2);
}
