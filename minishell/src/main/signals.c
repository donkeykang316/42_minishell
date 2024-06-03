/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:13:52 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/03 19:38:02 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler_parent(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_child(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int num)
{
	(void)num;
}

void	set_signals_parent(void)
{
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, sigquit_handler);
}

void	set_signals_child(void)
{
	signal(SIGQUIT, sigint_handler_child);
	/*signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler);*/
}
