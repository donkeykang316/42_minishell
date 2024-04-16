/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:12:42 by kaan              #+#    #+#             */
/*   Updated: 2024/04/16 09:43:26 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	operator_dollar(t_prompt *prompt)
{
	t_tmp	temp;

	if (ft_strchr(prompt->parser->cmd, 61))
	{
		temp.d_char = ft_split(prompt->parser->cmd, 61);
		if (!temp.d_char[0] || !temp.d_char[1])
		{
			printf("test\n");
			free_double_ptr(temp.d_char);
			return ;
		}
		
	}
}
