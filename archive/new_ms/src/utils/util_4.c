/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:43:47 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 17:51:36 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	parser_size(t_parser *parser)
{
	t_parser	*temp;
	size_t		size;

	temp = parser;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

char	*ft_strjoin_ms(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*appended;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	appended = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!appended)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		appended[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		appended[i++] = s2[j++];
	appended[i] = '\0';
	free(s1);
	return (appended);
}

bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}
