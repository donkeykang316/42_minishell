/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:38 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/10 15:33:46 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_token
{
	char	*value;
	int		type;
	struct	s_token	*next;
}	t_token;

typedef enum
{
	T_WORD = 1,
	T_PIPE = 2,
	T_GREATER = 3,
	T_LESSER = 4,
	T_HEREDOC = 5,
	T_APPEND = 6,
	
} tokennames;

void tokenize(char *str, t_token **token);
t_token	*ft_lstnew_ms(char *content);
t_token	*ft_lstlast_ms(t_token *lst);
void	ft_lstadd_back_ms(t_token **lst, t_token *new);
void	print_stack(t_token **tokens);
void	ft_free(t_token **tokens);
char	*ft_strdup_ms(char *s1);
int	ft_strlen_ms(char *s);

#endif