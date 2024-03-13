/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:41:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 18:17:28 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

//prototyping global struct
typedef struct s_global t_global;

//gives num values to operators (tokenizes)
typedef enum s_tokens
{
	T_WORD = 0,
	T_PIPE = 1,
	T_GREATER = 2,
	T_LESSER = 3,
	T_HEREDOC = 4,
	T_APPEND = 5,	
}	t_tokens;

//struct for lexer linked list
//stores words(delimited by whitespace), tokens (from s_token struct),
//position in the index, adresses of previous and next nodes
typedef struct s_lexer
{
	char			*word;
	t_tokens		token;
	int				index;
	struct s_lexer	*prev;
	struct s_lexer	*next;
} t_lexer;

// token_process.c
int	prompt_lexing(t_global **global);
int create_node(t_global **global, int	i);

// utils/lexer_utils.c
t_lexer	*lexernew_ms(char *word, int token);
void	lexeraddback_ms(t_lexer **lst, t_lexer *new);
t_lexer *lexerfreelist_ms(t_lexer **lst);

// utils/lexer_utils2.c
int is_whitespace(char c);
int is_whitespace_null(char c);
char *trim_whitespace(char *str);
int	ft_memcmp_ms(const void *s1, const void *s2);
int	ft_strlen_ms(char *s);
int	check_token(char *str);

#endif