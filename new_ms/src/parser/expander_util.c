/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:26:15 by kaan              #+#    #+#             */
/*   Updated: 2024/06/14 13:46:56 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_status;

size_t	exp_size(char *input_at_i, size_t *i, t_shell *shell)
{
	size_t	var_size;
	char	*var_name;
	char	*var_value;

	*i += 1;
	if (single_dollar(input_at_i))
		return (1);
	var_size = 0;
	while (input_at_i[var_size + 1]
		&& input_at_i[var_size + 1] != ' '
		&& !is_onstr(QUOTES, input_at_i[var_size + 1])
		&& input_at_i[var_size + 1] != '$')
		var_size++;
	if (var_size == 0)
		return (0);
	var_name = ft_substr(input_at_i, 1, var_size);
	var_value = get_envp(var_name, &shell->envp_lst);
	free(var_name);
	*i += var_size;
	if (!var_value)
		return (0);
	return (ft_strlen(var_value));
}

int	expander_size(char *input, t_shell *shell)
{
	size_t	i;
	size_t	size;
	bool	in_quotes;
	bool	in_dquotes;

	init_vars(&i, &size, &in_quotes, &in_dquotes);
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			size += exit_status_size() - 1;
			i++;
		}
		else if (input[i] == '$' && !in_quotes)
			size += exp_size(&(input[i]), &i, shell) - 1;
		else
			i++;
		size++;
	}
	return (size);
}

size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status_x;
	size_t	j;

	*i += 2;
	exit_status_x = ft_itoa(exit_status);
	j = 0;
	while (exit_status_x[j])
	{
		expanded_input_at_i[j] = exit_status_x[j];
		j += 1;
	}
	free(exit_status_x);
	return (j);
}

size_t	expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_shell *shell)
{
	char	*var_value;
	size_t	size;
	size_t	j;
	size_t	k;

	size = 0;
	j = 0;
	k = 0;
	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		expanded_input_at_i[0] = '$';
		return (1);
	}
	while (input[*i + size] && input[*i + size] != ' '
		&& input[*i + size] != '\"' && !is_onstr(QUOTES, input[*i + size])
		&& input[*i + size] != '$')
		size += 1;
	var_value = get_varvalue_envp(ft_substr(input, *i, size), shell);
	*i += size;
	if (!var_value)
		return (0);
	while (var_value[k])
		expanded_input_at_i[j++] = var_value[k++];
	return (j);
}
