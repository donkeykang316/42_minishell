/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/12 14:40:35 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char	*value;
	int		type;
	struct	s_token	*next;
}	t_token;

typedef enum
{
	T_WORD = 1,
	T_PIPE = 200,
	T_GREATER = 300,
	T_LESSER = 400,
	T_HEREDOC = 500,
	T_APPEND = 600,
	
} operators;

typedef enum
{
	T_ECHO = 10,
	T_CD = 20,
	T_PWD = 30,
	T_EXPORT = 40,
	T_UNSET = 50,
	T_ENV = 60,
	T_EXIT = 70,
	
} commands;

//lexing_token.c
void tokenize(char *str, t_token **token);
t_token	*ft_lstnew_ms(char *content);
t_token	*ft_lstlast_ms(t_token *lst);
void	ft_lstadd_back_ms(t_token **lst, t_token *new);
void	print_stack(t_token **tokens);
void	ft_free(t_token **tokens);
char	*ft_strdup_ms(char *s1);
int	ft_strlen_ms(char *s);

//defining.c
void assignment(t_token **tokens);
void	find_type(t_token *node);
int		find_cmd(t_token *node);
int		find_op(t_token *node);
int	ft_memcmp_ms(const void *s1, const void *s2);

#endif