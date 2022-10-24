/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_check_permissions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 03:19:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 22:56:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	change_pwds(t_env *env, char *oldpwd)
{
	char	*pwd;

	if (oldpwd && env_exist(env, "OLDPWD"))
		env_change_content(env, "OLDPWD", oldpwd);
	if (env_exist(env, "PWD"))
	{
		pwd = getcwd(0, 0);
		if (!pwd)
			return ;
		env_change_content(env, "PWD", pwd);
		free(pwd);
	}
}

int	cd_check_permissions(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
		return (1);
	}
	if (!(path_stat.st_mode & X_OK))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}

int	cd_exec_cmd(t_env *env, char *path)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		ft_putendl_fd(\
"cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
	if (chdir(path) < 0)
	{
		if (oldpwd)
			free(oldpwd);
		ft_ret_exit(0, 1);
		return (1);
	}
	change_pwds(env, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}
