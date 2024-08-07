/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:21:56 by mdomnik           #+#    #+#             */
/*   Updated: 2024/06/05 18:40:53 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

char *ft_getenv(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			if(env[i][ft_strlen(key)] == '=')
			{
				value = ft_strdup(ft_strchr(env[i], '=') + 1);
				return (value);
			}
		i++;
	}
	return (NULL);
}

void	adjust_lexer_redir(t_shell *shell)
{
	t_lexer	*lexer;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		if (lexer->token != T_WORD)
		{
			if (lexer->next != NULL && lexer->next->token == T_WORD)
				lexer->next->join = 1;
		}
		lexer = lexer->next;
	}
}

void check_final_lexer(t_shell *shell)
{
	t_lexer *lexer;

	lexer = shell->lexer;
	while (lexer->next != NULL)
	{
		if (find_redir(lexer->word) != 0 && lexer->next->token == T_PIPE)
			reset_loop(shell, ERR_SYNTAX, shell->parser->cmd);
		lexer = lexer->next;
	}
	if (find_redir(lexer->word) != 0)
		reset_loop(shell, ERR_SYNTAX, NULL);
}

void	raise_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		i;
	int		j;
	int		lvl;

	shlvl = ft_getenv("SHLVL", shell->env);
	lvl = ft_atoi(shlvl);
	lvl++;
	free(shlvl);
	shlvl = ft_itoa(lvl);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin_ms("SHLVL=", shlvl);
			break ;
		}
		i++;
	}
	j = 0;
	while (shell->declare[j])
	{
		if (ft_strncmp(shell->declare[j], "SHLVL=", 6) == 0)
		{
			free(shell->declare[i]);
			shell->declare[i] = ft_strdup(shell->env[i]);
			break ;
		}
		j++;
	}
}

