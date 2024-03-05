/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:54 by kaan              #+#    #+#             */
/*   Updated: 2024/03/05 18:40:01 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	echo_init(t_echo *var)
{
	var->pr = NULL;
	var->temp1 = NULL;
	var->temp2 = NULL;
	var->i = 0;
}

static void	free_echo(t_echo *var)
{
	if (var->pr)
		free(var->pr);
	if (var->temp1)
		free(var->temp1);
	if (var->temp2)
		free(var->temp2);
}

void	ft_echo_n(const char *str)
{
	char	*pr;

	pr = ft_substr(str, 8, ft_strlen(str));
	printf("%s%c\n", pr, '%');
	free(pr);
}

static void	quotation_case(const char *str, int c, t_echo *var)
{
	if (str[ft_strlen(str) - 1] == c)
	{
		var->i = 0;
		while (str[var->i] != c)
			var->i++;
		var->pr = ft_substr(str, var->i + 1, ft_strlen(str) - 1);
		var->pr[ft_strlen(var->pr) - 1] = '\0';
		printf("%s\n", var->pr);
		return ;
	}
	else
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
				printf("%s\n", var->pr);
				return ;
			}
		}
	}
}

void	ft_echo(const char *str)
{
	t_echo	var;

	echo_init(&var);
	if (ft_strchr(str, 34))
		quotation_case(str, 34, &var);
	else if (ft_strchr(str, 39))
		quotation_case(str, 39, &var);
	else
	{
		var.i = 5;
		while (str[var.i] == 32)
			var.i++;
		var.pr = ft_substr(str, var.i, ft_strlen(str));
		printf("%s\n", var.pr);
	}
	free_echo(&var);
}
