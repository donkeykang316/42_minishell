/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:28:57 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/21 18:10:26 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_shell *shell)
{
	print_expand(shell);
	parser_exec(shell);
}

void parser_exec(t_shell *shell)
{
	t_expand	*expand;
	char		***redirections;
	
	expand = shell->expand;
	while(expand->next != NULL)
	{
		redirections = group_io(shell, expand);
		remove_redir_nodes(shell, expand);
		create_cmd_node(shell, expand);
		create_redir_nodes(shell, redirections);
		print_expand(shell);
		print_exec(shell);
	}
	// adjust_redir(shell, expand);
	execution(shell);
}

char	***group_io(t_shell *shell, t_expand *expand)
{
	int		redir_count;
	char 	***redirections;

	redir_count = 0;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token != T_WORD && expand->token != T_PIPE)
			redir_count++;
		expand = expand->next;
	}
	printf("redir_count: %d\n", redir_count);
	redirections = (char ***)malloc((redir_count + 1) * sizeof(char **));
	expand = shell->expand;
	redir_count = 0;
	while (expand != NULL && expand->token != T_PIPE)
	{
		if (expand->token != T_WORD && expand->token != T_PIPE)
		{
			redirections[redir_count] = (char **)malloc(3 * sizeof(char *));
			redirections[redir_count][0] = ft_strdup(expand->word);
			redirections[redir_count][1] = ft_strdup(expand->next->word);
			redirections[redir_count][2] = NULL;
			redir_count++;
		}
		expand = expand->next;
	}
	redirections[redir_count] = NULL;
	print_triple_pointer(redirections);
	return (redirections);
}

void	create_cmd_node(t_shell *shell, t_expand *expand)
{
	char **args;
	int	i;

	i = 0;
	while(expand != NULL && expand->token != T_PIPE)
	{
		i++;
		expand = expand->next;
	}
	args = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	expand = shell->expand;
	while(expand != NULL && expand->token != T_PIPE)
	{
		args[i] = ft_strdup(expand->word);
		i++;
		expand = expand->next;
	}
	args[i] = NULL;
	create_exec_node(shell, args, NONE);
	free_double(args);
	remove_pipe_and_prev(shell, expand);
}

void create_redir_nodes(t_shell *shell, char ***redir)
{
	int	i;
	char **args;

	i = 0;
	while (redir[i] != NULL)
	{
		args = malloc(2 * sizeof(char *));
		args[0] = ft_strdup(redir[i][1]);
		args[1] = NULL;
		create_exec_node(shell, args, find_redir(redir[i][0]));
		free_double(args);
		i++;
	}
	free_triple_pointer(redir);
}
void adjust_redir(t_shell *shell, t_expand *expand)
{
	(void)shell;
	(void)expand;
}
