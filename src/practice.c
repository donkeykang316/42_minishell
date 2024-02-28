/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:52:54 by kaan              #+#    #+#             */
/*   Updated: 2024/02/28 22:03:51 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
 	char	*str;

	str = readline("Enter prompt: ");
	if (str)
		printf("%s\n", str);
	else
		printf("readline error\n");
	free(str); 
	/* char *path = getenv("PATH");

    if (path != NULL) {
        printf("The value of PATH is: %s\n", path);
    } else {
        printf("PATH environment variable is not set\n");
    }*/
}
