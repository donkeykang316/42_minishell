/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:20:11 by kaan              #+#    #+#             */
/*   Updated: 2024/06/22 14:18:23 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

char	**add_string(char **array, int *size, const char *new_string)
{
	char	**new_array;
	int		i;

	new_array = malloc((*size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *size)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[*size] = ft_strdup(new_string);
	free_d_lst(array);
	array = malloc((*size + 2) * sizeof(char *));
	i = 0;
	while (i < *size + 1)
	{
		array[i] = ft_strdup(new_array[i]);
		i++;
	}
	i = 0;
	while (new_array[i] && i < *size + 1)
	{
		free(new_array[i]);
		i++;
	}
	free(new_array);
	(*size)++;
	return (array);
}

t_parser	*cat_parser(t_parser *parser)
{
	t_parser *first;
	t_parser *third;
	int	size;
	int	i;

	first = parser;
	size = get_token_count(first->token);
	i = 0;
	while (first->next->token[i])
	{
		first->token = add_string(first->token, &size, first->next->token[i]);
		i++;
	}
	first->token[i + 1] = NULL;
	first->operator = first->next->operator;
	free_d_lst(first->next->token);
	free(first->next);
	if (parser->next->next)
	{
		third = parser->next->next;
		first->next = third;
	}
	return (first);
}

void	less(t_shell *shell, t_parser *parser)
{
	int		fd;

	fd = 0;
	if (parser->next->token[0])
	{
		while (parser->operator == LESS)
		{
			parser->operator = NONE;
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile();
			else if (access(parser->next->token[0], R_OK) == -1)
				less_nopermit_exit(shell);
			parser = parser->next;
		}
		while (parser->operator == LESS)
		{
			parser->operator = NONE;
			if (access(parser->next->token[0], F_OK) == -1)
				less_nofile();
			else if (access(parser->next->token[0], R_OK) == -1)
				less_nopermit_exit(shell);
			parser = parser->next;
		}
		//ft_putnbr_fd(parser->token_count, 2);
		//perror(parser->token[0]);
		if (parser->token_count > 2
			&& parser->token[1])
			less_multi_file(shell, parser, fd);
		else if (access(parser->token[0], F_OK) == 0)
			less_one_file(shell, parser, fd);
		else if (pipe_check(parser) && input_redir_check(parser))
			less_invalid_input(parser->token[0]);
	}
}

void	heredoc(t_parser *parser)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (strcmp_ms(buff, parser->next->token[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	ft_open(char *token, int option)
{
	if (open(token, O_WRONLY | option | O_CREAT, 0666) == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}
}

void	redir_output(t_parser *parser)
{
	close(STDOUT_FILENO);
	while (parser->next->operator == GREAT
		|| parser->next->operator == APPEND)
	{
		if (parser->operator == GREAT)
			ft_open(parser->next->token[0], O_TRUNC);
		else if (parser->operator == APPEND)
			ft_open(parser->next->token[0], O_APPEND);
		parser = parser->next;
		close(STDOUT_FILENO);
	}
	if (parser->operator == GREAT)
	{
		ft_open(parser->next->token[0], O_TRUNC);
		free_d_lst(parser->next->token);
		free(parser->next);
	}
	else if (parser->operator == APPEND)
	{
		ft_open(parser->next->token[0], O_APPEND);
		free_d_lst(parser->next->token);
		free(parser->next);
	}
}

void	redir_exe(t_shell *shell, t_parser *parser)
{
	t_parser	*temp;

	temp = parser;
	if (parser->operator == LESS)
		less(shell, parser);
	else if (parser->operator == HEREDOC)
		heredoc(parser);
	else
		redir_output(parser);
	//print_parser(temp);
	//temp->operator = NONE;
	if (!input_redir_check(temp))
		temp = cat_parser(temp);
	print_parser(temp);
	//print_token(temp->token);
	/*while (parser->operator != NONE && parser->operator != PIPE)
		parser = parser->next;*/
	if (parser->operator == NONE)
		exec_cmd(shell, temp);
	else
		pipe_exe(shell, parser);
}
