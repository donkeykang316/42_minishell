/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:45 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/14 13:50:36 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//checks whether a character is a whitespace (space, tabs, carrage ret)
int is_whitespace_null(char c)
{
	if (c == 32 || (c >= 9 && c <= 13) || c == '\0')
		return(1);
	return(0);
}

int is_quote(char c)
{
	if (c == 34 || c == 39)
		return(1);
	return(0);
}

//gets rid of all the whitespace before and after the string
char *trim_whitespace(char *str)
{
	char *temp;
	int	 i;
	int	 j;
	int	 k;

	j = (ft_strlen(str) - 1);
	i = 0;
	k = 0;
	while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while(str[j] == 32 || (str[j] >= 9 && str[j] <= 13))
		j--;
	temp = (char *)malloc(((j - i) + 1) * sizeof(char));
	if (!temp)
		printf("oh no\n"); //change to an actual error exit sequence
	while((i + k) <= j)
	{
		temp[k] = str[i + k];
		k++;
	}
	temp[k] = '\0';
	return(temp);
}

//changed version of memcmp, checks the entire string,
//looking for the perfect match
int	ft_memcmp_ms(const void *s1, const void *s2)
{
	char	*p1;
	char	*p2;
	int		i;
	int		len;

	p1 = (char *)s1;
	p2 = (char *)s2;
	len = ft_strlen_ms(p1);
	i = 0;
	if (len != ft_strlen_ms(p2))
		return (-1);
	while (i < len)
	{
		if (p1[i] != p2[i])
		{
			return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
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


//compares the string with names of tokens, if perfect comparison,
//then assigns corresponding value
int	check_token(char *str)
{
	if (!ft_memcmp_ms(str, "|"))
		return(T_PIPE);
	else if (!ft_memcmp_ms(str, ">"))
		return(T_GREATER);
	else if (!ft_memcmp_ms(str, "<"))
		return(T_LESSER);
	else if (!ft_memcmp_ms(str, "<<"))
		return(T_HEREDOC);
	else if (!ft_memcmp_ms(str, ">>"))
		return(T_APPEND);
	return (T_WORD);
}

int finddollar_typecheck(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$')
			if (c == 34)
				return (1);
		i++;
	}
	return(0);
}