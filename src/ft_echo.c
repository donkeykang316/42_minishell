/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/03/06 10:19:24 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	case_loop(char *str, int c, t_echo *var, char *end)
{
	var->i = 0;
	var->temp1 = ft_strjoin(ft_substr(str, var->i, ft_strlen(str)), "\n");
	while (1)
	{
		var->temp2 = readline("quote> ");
		var->temp2 = ft_strjoin(var->temp2, "\n");
		var->temp1 = ft_strjoin(var->temp1, var->temp2);
		if (var->temp1[ft_strlen(var->temp1) - 2] == c)
		{
			var->temp1[ft_strlen(var->temp1) - 1] = '\0';
			add_history(var->temp1);
			while (str[var->i] != c)
				var->i++;
			var->pr = ft_substr(var->temp1, var->i + 1,
					ft_strlen(var->temp1) - 1);
			var->pr[ft_strlen(var->pr) - 1] = '\0';
			printf("%s%s", var->pr, end);
			return ;
		}
	}
}

static void	quotation_case(char *str, int c, t_echo *var, char *end)
{
	if (str[ft_strlen(str) - 1] == c)
	{
		var->i = 0;
		while (str[var->i] != c)
			var->i++;
		var->pr = ft_substr(str, var->i + 1, ft_strlen(str) - 1);
		var->pr[ft_strlen(var->pr) - 1] = '\0';
		printf("%s%s", var->pr, end);
		return ;
	}
	else
		return (case_loop(str, c, var, end));
}

static void	std_echo(char *str, t_echo *var, int n, char *end)
{
	var->i = 5;
	while (str[var->i] != n)
		var->i++;
	var->i++;
	while (str[var->i] == 32)
		var->i++;
	var->pr = ft_substr(str, var->i, ft_strlen(str));
	printf("%s%s", var->pr, end);
}

void	ft_echo(char *str)
{
	t_echo	var;

	echo_init(&var);
	if (ft_strnstr(str, "-n", ft_strlen(str)))
	{
		if (ft_strchr(str, 34))
			quotation_case(str, 34, &var, "\0");
		else if (ft_strchr(str, 39))
			quotation_case(str, 39, &var, "\0");
		else
			std_echo(str, &var, 110, "\0");
	}
	else
	{
		if (ft_strchr(str, 34))
			quotation_case(str, 34, &var, "\n");
		else if (ft_strchr(str, 39))
			quotation_case(str, 39, &var, "\n");
		else
			std_echo(str, &var, 32, "\n");
	}
	free_echo(&var);
	free(str);
}
