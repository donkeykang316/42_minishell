/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:45 by mdomnik           #+#    #+#             */
/*   Updated: 2024/03/13 12:49:11 by mdomnik          ###   ########.fr       */
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