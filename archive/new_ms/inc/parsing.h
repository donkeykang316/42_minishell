/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:24:44 by kaan              #+#    #+#             */
/*   Updated: 2024/06/17 21:16:12 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_parser	t_parser;
typedef enum e_operator	t_operator;

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
t_parser	*p_new_node(int token_count);
bool		single_dollar(char *input_at_i);
int			get_token_count(char **token);

#endif
