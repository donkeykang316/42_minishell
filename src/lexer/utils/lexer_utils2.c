/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:45 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 14:46:06 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

//checks whether a character is a whitespace (space, tabs, carrage ret)
int is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
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