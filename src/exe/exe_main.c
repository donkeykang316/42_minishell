/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:52:02 by kaan              #+#    #+#             */
/*   Updated: 2024/04/16 09:27:58 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	exe_main(t_prompt *prompt)
{
	ft_echo(prompt);
	ft_pwd(prompt);
	ft_cd(prompt);
	ft_env(prompt);
	operator_dollar(prompt);
	cmd_exit(prompt);
}