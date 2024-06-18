/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:52:14 by kaan              #+#    #+#             */
/*   Updated: 2024/06/18 13:55:19 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

void	less_nofile_exit(void)
{
	ft_putendl_fd(NO_FILE, STDERR_FILENO);
	//exit(EXIT_FAILURE);
}

void	less_multi_file(t_parser *parser, int fd)
{
	int	i;

	i = 1;
	while (parser->token[i]
		&& access(parser->token[i], F_OK) == 0)
	{
		fd = open(parser->token[i], O_RDONLY, 0666);
		dup2(fd, STDIN_FILENO);
		i++;
	}
}

void	less_one_file(t_parser *parser, int fd)
{
	fd = open(parser->token[0], O_RDONLY, 0666);
	dup2(fd, STDIN_FILENO);
}

void	less_invalid_input(char *token)
{
	char	*err_msg;

	err_msg = ft_strjoin("minishell: ", token);
	perror(err_msg);
	free(err_msg);
	exit_status = 2;
	exit(EXIT_FAILURE);
}
