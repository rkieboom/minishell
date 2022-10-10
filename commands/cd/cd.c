/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:29:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/10 13:23:55 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	cd_check_exist(char *PATH)
{
	DIR	*directory;

	directory = opendir(PATH);
	if (!directory)
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (closedir(directory) < 0)
		ft_ret_exit(1, 1);
	return (0);
}

static int	cd_1_arg(t_list *v)
{
	int		ret;

	if (!ft_strncmp(search_env(v->env, "HOME", 0), "", 1))
	{
		ft_putstr_fd("minishell-4.2$: cd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		env_change_content(v->env, "OLDPWD", search_env(v->env, "PWD", 3));
		ret = chdir(search_env(v->env, "HOME", 0));
		if (ret < 0)
			ft_ret_exit(0, 1);
		env_change_content(v->env, "PWD", search_env(v->env, "HOME", 4));
	}
	return (0);
}

static int	cd_check_if_dir_and_perms(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		ft_ret_exit(1, 1);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putendl_fd("minishell-4.2$: Not a directory", 2);
		return (1);
	}
	else if (!(path_stat.st_mode & X_OK))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}

int	cd(t_list *v, char **str)
{
	int		ret;
	char	*newpath;
	char	cwd[4096];

	check_pwd_oldpwd(v->env);
	if (!str[1])
		return (cd_1_arg(v));
	newpath = cd_tilde_expansion(v, str[1]);
	if (!newpath)
		return (1);
	if (cd_check_exist(newpath) || cd_check_if_dir_and_perms(newpath))
	{
		free(newpath);
		return (1);
	}
	if (!getcwd(cwd, 4096))
		return (nonworkingdir(v, newpath));
	env_change_content(v->env, "OLDPWD", cwd);
	ret = chdir(newpath);
	if (ret < 0)
		ft_ret_exit(0, 1);
	if (getcwd(cwd, 4096))
		env_change_content(v->env, "PWD", cwd);
	free(newpath);
	return (0);
}
