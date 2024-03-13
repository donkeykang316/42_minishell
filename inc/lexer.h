/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:41:48 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 13:23:23 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//struct for lexer linked list
//stores words(delimited by whitespace), tokens (from s_token struct),
//position in the index, adresses of previous and next nodes

//gives num values to operators (tokenizes)
typedef enum s_tokens
{
	T_PIPE = 1,
	T_GREATER = 2,
	T_LESSER = 3,
	T_HEREDOC = 4,
	T_APPEND = 5,	
}	t_tokens;

typedef struct s_lexer
{
	char			*word;
	t_tokens		token;
	int				index;
	struct t_lexer	*prev;
	struct t_lexer	*next;
} t_lexer;

// token_process.c
int	prompt_lexing(t_global **global);

// utils/lexer_utils.c
t_lexer	*lexernew_ms(char *word, int token);
void	lexeraddback_ms(t_lexer **lst, t_lexer *new);
t_lexer *lexerfreelist_ms(t_lexer **lst);

// utils/lexer_utils2.c
int is_whitespace(char c);

#endif