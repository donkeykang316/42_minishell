/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:52:14 by kaan              #+#    #+#             */
/*   Updated: 2024/03/07 12:03:07 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cd_init(t_cd *var)
{
	var->dpath = NULL;
	var->pwd = NULL;
	var->len = 0;
}

void	ft_chdir(char *str, char *pwd)
{
	if (chdir(pwd))
		printf("%s: No such directory\n", str);
}
