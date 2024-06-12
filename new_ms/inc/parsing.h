/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:24:44 by kaan              #+#    #+#             */
/*   Updated: 2024/06/12 16:11:15 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_parser	t_parser;

//pre_process
bool	valid_input(char *input, t_shell *shell);

//syntax
bool	invalid_syntax(char *input);
bool	invalid_syntax2(char *input);
bool	invalid_syntax_on_operator(char *input);
bool	is_onstr(const char *str, int ch);
bool	has_operator(char *input);
bool	is_spaces(char c);

//expander
char	*expanding(char *input, t_shell *shell);
int		expander_size(char *input, t_shell *shell);
size_t	expand_exit_status(char *expanded_input_at_i, size_t *i);
size_t	expand_variable(char *expanded_input_at_i, char *input,
			size_t *i, t_shell *shell);
size_t	exit_status_size(void);
void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes);

//tokenizer
char	**tokenizer(char *input);

//parser
t_parser	*parsing(char *input);

#endif
