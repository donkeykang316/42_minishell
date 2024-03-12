/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexical_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/12 20:12:50 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	tok_loop(char *str, t_lextmp *tp)
{
	while (str[tp->i + tp->j] != ' ' && str[tp->i + tp->j] != '\n'
		&& str[tp->i + tp->j] != '\t' && str[tp->i + tp->j] != '\0')
		tp->j++;
	tp->data = malloc((tp->j + 1) * sizeof(char));
	tp->j = 0;
	while (str[tp->i] != ' ' && str[tp->i] != '\n'
		&& str[tp->i] != '\t' && str[tp->i] != '\0')
	{
		tp->data[tp->j] = str[tp->i];
		tp->j++;
		tp->i++;
	}
	tp->data[tp->j] = '\0';
}

// skips whitespaces, and creates nodes from
// strings seperated by the whitespaces
void	tokenize(char *str, t_token **token)
{
	t_token	*temp;
	t_lextmp	tp;

	tp.i = 0;
	while (str[tp.i] != '\0')
	{
		tp.j = 0;
		if (str[tp.i] != ' ' && str[tp.i] != '\n'
			&& str[tp.i] != '\t' && str[tp.i] != '\0')
		{
			tok_loop(str, &tp);
			temp = ft_lstnew_ms(tp.data);
			ft_lstadd_back_ms(token, temp);
			free(tp.data);
		}
		if (str[tp.i] == '\0')
			break ;
		tp.i++;
	}
}

// creates new nodes, with parameters of t_token
t_token	*ft_lstnew_ms(char *content)
{
	t_token	*element;

	element = (t_token *)malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->value = ft_strdup_ms(content);
	element->type = 0;
	element->next = NULL;
	return (element);
}

//adds new node to the back of the list
void	ft_lstadd_back_ms(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ft_lstlast_ms(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
		new->next = NULL;
	}
}

// finds the last element of the list
t_token	*ft_lstlast_ms(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}
