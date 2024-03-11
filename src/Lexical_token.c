/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexical_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:15:09 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/11 14:47:12 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// main
int	main(void)
{
	char	*str;
	char	*temp;
	t_token	*tokens;
	
	tokens = NULL;
	temp = NULL;
	while (1)
	{
		str = readline("[minishell]$ ");
		tokenize(str, &tokens);
		assignment(&tokens);
		print_stack(&tokens);
		ft_free(&tokens);
		free(str);
	}
	return (0);
}

// skips whitespaces, and creates nodes from strings seperated by the whitespaces
void tokenize(char *str, t_token **token)
{
	t_token	*temp;
	char	*data;
	int		i;
	int		j;

	i = 0;
	while(str[i] != '\0')
	{
		j = 0;
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\0')
		{
			while(str[i + j] != ' ' && str[i + j] != '\n' && str[i + j] != '\t' && str[i + j] != '\0')
				j++;
			data = malloc((j + 1) * sizeof(char));
			j = 0;
			while(str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\0')
			{
				data[j] = str[i];
				j++;
				i++;
			}
			data[j] = '\0';
			temp = ft_lstnew_ms(data);
			ft_lstadd_back_ms(token, temp);
			free(data);
		}
		if (str[i] == '\0')
			break ;
		i++;
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

//prints the entire stack (linked list)
void	print_stack(t_token **token)
{
	t_token	*current;
	current = (*token);
	if (token == NULL)
	{
		printf("Stack is empty\n");
	}
	printf("Stack contents:\n");
	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

// frees the stack
void	ft_free(t_token **tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}

// duplicates string
char	*ft_strdup_ms(char *s1)
{
	char	*dest;
	size_t	i;

	dest = (char *) malloc(ft_strlen_ms(s1) + 1);
	i = 0;
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

// finds length of string
int	ft_strlen_ms(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}