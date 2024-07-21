/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:02:12 by kaan              #+#    #+#             */
/*   Updated: 2024/06/13 13:07:28 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	perror_cd(char *path)
{
	char	*msg;	

	msg = ft_strjoin("minishell: cd: ", path);
	perror(msg);
	free(msg);
	return (EXIT_FAILURE);
}

void	update_oldpwd(char *temp, t_shell *shell)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", temp);
	save_user_vars(oldpwd, &shell->envp_lst, true);
	free(oldpwd);
}

void	update_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*updated_var;

	getcwd(cwd, PATH_MAX);
	updated_var = ft_strjoin("PWD=", cwd);
	save_user_vars(updated_var, &shell->envp_lst, true);
	free(updated_var);
}

int	cd_oldpwd(char *temp, t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_envp("OLDPWD", &shell->envp_lst);
	if (!oldpwd)
	{
		ft_putendl_fd(OLDPWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(&temp[0], shell);
		update_pwd(shell);
		return (EXIT_SUCCESS);
	}
	return (perror_cd(oldpwd));
}

int	cd_util(char *path, t_shell *shell)
{
	char	temp[PATH_MAX];

	getcwd(temp, PATH_MAX);
	if (path == NULL || strcmp_ms(path, "~"))
	{
		update_oldpwd(&temp[0], shell);
		chdir(getenv("HOME"));
		update_pwd(shell);
		return (EXIT_SUCCESS);
	}
	if (strcmp_ms(path, "-"))
		return (cd_oldpwd(&temp[0], shell));
	if (chdir(path) == SUCCESS)
	{
		update_oldpwd(&temp[0], shell);
		update_pwd(shell);
		return (EXIT_SUCCESS);
	}
	return (perror_cd(path));
}
