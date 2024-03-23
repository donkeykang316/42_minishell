/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:01:19 by kaan              #+#    #+#             */
/*   Updated: 2024/03/23 12:08:06 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

int	shell_reset(int nbr)
{
	return (nbr - 0);
}

void	handle_ctrlc(int sig)
{
	(void)sig;
	//ft_putstr_fd(CL_NAME, 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_redisplay();
}

void	handle_ctrld(int sig)
{
	(void)sig;
	ft_putstr_fd("exit", 1);
	exit(0);
}

void	shell_loop(t_prompt *prompt)
{
	/*int	nbr;

	nbr = 0;*/
	while (1)
	{
		/* if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_exit("quit\n"); */
		signal(SIGQUIT, handle_ctrld);
		signal(SIGINT, handle_ctrlc);
		prompt->line = readline(CL_NAME);
		if (!prompt->line)
			ft_exit("quit minishell");
		split_tokens(prompt);
		add_history(prompt->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;

	(void)argv;
	(void)envp;
	if (argc != 1)
		ft_exit("Excute the program without addtional argument\n");
	prompt = NULL;
	prompt = init_prompt(prompt);
	prompt->envp->env = double_dup(envp);
	if (!prompt->envp->env)
		simple_err(ERR_ENV);
	shell_loop(prompt);
}
