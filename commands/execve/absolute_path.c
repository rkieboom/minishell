/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   absolute_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:02:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/02/06 18:03:28 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	check_fullpath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_path(char *name, char *ENV_PATH) //protection and leaks
{
	int		i;
	int		fd;
	char	**paths;
	char	*newpath;

	i = 0;
	paths = ft_split(ENV_PATH, ':');
	while (paths[i])
	{
		newpath = ft_strdup(paths[i]);
		newpath = ft_strjoin(newpath, "/");
		newpath = ft_strjoin(newpath, name);
		fd = open(newpath, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			return (newpath);
		}
		free(newpath);
		i++;
	}
	return (NULL);
}

char	*absolute_path(char *PATH, t_env *env)
{
	char	*newpath;

	newpath = 0;
	if (!check_fullpath(PATH))
		newpath = get_path(PATH, search_env(env, "PATH", 4));
	if (!newpath)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": command not found", 2);
		return (NULL);
	}
	if (check_permission(newpath))
		return (NULL);
	return (newpath);
}
