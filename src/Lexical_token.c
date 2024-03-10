/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexical_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/10 13:16:44 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*str;
	char	*temp;

	temp = NULL;
	while (1)
	{
		str = readline("[minishell]$ ");
		tokenize(str);
	}
	free(str);
	return (0);
}

void tokenize(char *str)
{
	t_token **token;
	t_token *new;

	char	*data;
	int		i;
	int		j;

	token = NULL;
	data = NULL;
	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
		{
			while(str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			{
				data[j] = str[i];
				j++;
				i++;
			}
			new = ft_lstnew_ms(data);
			ft_lstadd_back_ms(token, new);
		}
		i++;
	}
}

t_token	*ft_lstnew_ms(char *content)
{
	t_token	*element;

	element = (t_token *)malloc(sizeof(t_token));
	if (!element)
		return (NULL);
	element->value = content;
	element->type = NULL;
	element->next = NULL;
	return (element);
}

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