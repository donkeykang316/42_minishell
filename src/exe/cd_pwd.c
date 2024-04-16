/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:00:45 by kaan              #+#    #+#             */
/*   Updated: 2024/04/16 09:25:48 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exe.h"

void	ft_pwd(t_prompt *prompt)
{
	char	*pwd;

	if (!ft_memcmp_ms(prompt->parser->cmd, "pwd"))
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
}

void    ft_free(char **ptr)
{
    int     i;

    i = 0;
    if (ptr)
    {
        while (ptr[i])
        {
            free(ptr[i]);
            i++;
        }
    	free(ptr);
    }
}

char    *get_env(char **env, char *env_var)
{
    int     i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env_var, env[i], 4))
        	    return (env[i]);
        i++;
    }
    return (NULL);
}

char    *get_home(t_prompt *prompt)
{
    t_tmp   tmp;

    tmp.i = 0;
	tmp.d_char = ft_split(get_env(prompt->envp->env, "HOME"), 61);
    while (prompt->envp->env[tmp.i])
    {
        tmp.s_char = ft_strdup(tmp.d_char[tmp.i]);
		if (access(tmp.s_char, R_OK | X_OK) != -1)
		{
			ft_free(tmp.d_char);
        	return (tmp.s_char);
		}
    	free(tmp.s_char);
    	tmp.i++;
    }
	ft_free(tmp.d_char);
	return (NULL);
}

void	ft_cd(t_prompt *prompt)
{
	char	*path;
	if (!ft_memcmp_ms(prompt->parser->cmd, "cd"))
	{
		if (!prompt->parser->args[0])
		{
			path = get_home(prompt);
			chdir(path);
			return ;
		}
		if (prompt->parser->args[1])
		{
			printf("too many arguments\n");
			return ;
		}
		if (chdir(prompt->parser->args[0]))
		{
			printf("No such file or directory\n");
			return ;
		}
	}
}
