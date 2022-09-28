/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:29:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/27 18:30:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	cd_check_exist(char *PATH)
{
	struct stat	stats;
	int			fd;

	fd = open(PATH, O_RDONLY);
	if (fd < 0)
	{
		if (stat(PATH, &stats) == 0)
			return (0);
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	close(fd);
	return (0);
}

static int	cd_check_permission(char *PATH)
{
	struct stat	stats;

	if (stat(PATH, &stats) != 0)
		return (1);
	else if (!(stats.st_mode & X_OK))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}

static int	cd_1_arg(t_list *v)
{
	int		ret;
	char	cwd[1024];

	if (!ft_strncmp(search_env(v->env, "HOME", 0), "", 1))
	{
		ft_putstr_fd("minishell-4.2$: cd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		env_change_content(v->env, "OLDPWD", getcwd(cwd, 1024));
		ret = chdir(search_env(v->env, "HOME", 0));
		if (ret < 0)
			ft_ret_exit(ret, 1);
		env_change_content(v->env, "PWD", getcwd(cwd, 1024));
	}
	return (0);
}

static int	cd_check_dir(char *str)
{
	struct stat	path_stat;

	stat(str, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putendl_fd("minishell-4.2$: Not a directory", 2);
		return (1);
	}
	return (0);
}

int	cd(t_list *v, char **str)
{
	int		ret;
	char	cwd[1024];

	if (!str[1])
		return (cd_1_arg(v));
	if (cd_check_exist(str[1]) || cd_check_dir(str[1]) \
	|| cd_check_permission(str[1]))
		return (1);
	env_change_content(v->env, "OLDPWD", getcwd(cwd, 1024));
	ret = chdir(str[1]);
	if (ret < 0)
		ft_ret_exit(ret, 1);
	env_change_content(v->env, "PWD", getcwd(cwd, 1024));
	return (0);
}
