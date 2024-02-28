/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:52:54 by kaan              #+#    #+#             */
/*   Updated: 2024/02/28 22:28:33 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(const char *echo, char **av)
{
	char	*str;

	if (av[1] == "echo ")
	{
		str = readline(echo);
		if (str)
			printf("%s\n", str);
		else
			printf("readline error\n");
		free(str);
	}
}

int	main(int ac, char **av)
{
 	ft_echo("", av);
	/* char *path = getenv("PATH");

    if (path != NULL) {
        printf("The value of PATH is: %s\n", path);
    } else {
        printf("PATH environment variable is not set\n");
    }*/
}
