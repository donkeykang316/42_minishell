/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:00:45 by kaan              #+#    #+#             */
/*   Updated: 2024/04/14 06:00:15 by kaan             ###   ########.fr       */
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
	tmp.all_path = ft_split(get_env(prompt->envp->env, "HOME"), 61);
    while (prompt->envp->env[tmp.i])
    {
        tmp.path = ft_strdup(tmp.all_path[tmp.i]);
		if (access(tmp.path, R_OK | X_OK) != -1)
		{
			ft_free(tmp.all_path);
        	return (tmp.path);
		}
    	free(tmp.path);
    	tmp.i++;
    }
	ft_free(tmp.all_path);
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
