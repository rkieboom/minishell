/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:29:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 14:07:18 by rkieboom      ########   odam.nl         */
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

static int	go_home(t_env *env)
{
	char	*home;
	char	*oldpwd;

	if (!env_exist(env, "HOME") || !env_has_data(env, "HOME"))
	{
		ft_putendl_fd("minishell-4.2$: cd HOME not set", 2);
		return (1);
	}
	else
		home = env_get_content(env, "HOME");
	oldpwd = getcwd(0, 0);
	if (chdir(home) < 0)
	{
		ft_ret_exit(0, 1);
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	change_pwds(env, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

static	int	go_old_pwd(t_env *env)
{
	char	*oldpwd;
	char	*newold;

	if (!env_exist(env, "OLDPWD") || !env_has_data(env, "OLDPWD"))
	{
		ft_putendl_fd("minishell-4.2$: cd: OLDPWD not set", 2);
		return (1);
	}
	else
		oldpwd = env_get_content(env, "OLDPWD");
	newold = getcwd(0, 0);
	if (chdir(oldpwd) < 0)
	{
		if (newold)
			free(newold);
		ft_ret_exit(0, 1);
		return (1);
	}
	ft_putendl_fd(oldpwd, 2);
	change_pwds(env, newold);
	if (newold)
		free(newold);
	return (0);
}

int	cd(t_list *v, char **str)
{
	if (!str[1])
		return (go_home(v->env));
	else if (!ft_strncmp(str[1], "-", 2))
		return (go_old_pwd(v->env));
	else if (!str[1][0])
		return (0);
	else if (cd_check_permissions(str[1]))
		return (1);
	return (cd_exec_cmd(v->env, str[1]));
}
