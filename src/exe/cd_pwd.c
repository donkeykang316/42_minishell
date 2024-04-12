/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:00:45 by kaan              #+#    #+#             */
/*   Updated: 2024/04/12 13:31:21 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	ft_pwd(t_prompt *prompt)
{
	char	*pwd;

	if (!ft_memcmp_ms(prompt->parser->cmd, "pwd"))
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
}

void	ft_cd(t_prompt *prompt)
{
	if (!ft_memcmp_ms(prompt->parser->cmd, "cd"))
	{
		if (!prompt->parser->args[0])
		{
			printf("empty argument\n");
			return ;
		}
		if (prompt->parser->args[1])
		{
			printf("too many arguments\n");
			return ;
		}
		if (chdir(prompt->parser->args[0]))
		{
			printf("No such file or directory\n");
			return ;
		}
	}
}
