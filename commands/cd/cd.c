/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:29:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/12 10:26:34 by rkieboom      ########   odam.nl         */
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
		ft_putstr_fd("minishell: cd: ", 2);
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
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}

int	cd(t_list *v, char **str)
{
	char	*buf;
	char	cwd[255];

	buf = malloc(sizeof(char) * ft_strlen(str[1]));
	if (!buf)
		return (1);
	if (cd_check_exist(str[1]) || cd_check_permission(str[1]))
		return (1);
	env_change_content(v->env, "OLDPWD", getcwd(cwd, 255));
	if (buf && chdir(str[1]) < 0)
	{
		free(buf);
		ft_exit(1);
	}
	free(buf);//ff kijken
	env_change_content(v->env, "PWD", getcwd(cwd, 255));
	return (0);
}
