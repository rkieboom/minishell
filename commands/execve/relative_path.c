/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   relative_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:02:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/22 14:24:36 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	free_paths(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*create_path(char **paths, char *newpath, int i, char *name)
{
	char	*temp;

	newpath = ft_strdup(paths[i]);
	if (!newpath)
		ft_ret_exit(1, 1);
	temp = newpath;
	newpath = ft_strjoin(newpath, "/");
	if (!newpath)
		ft_ret_exit(1, 1);
	free(temp);
	temp = newpath;
	newpath = ft_strjoin(newpath, name);
	if (!newpath)
		ft_ret_exit(1, 1);
	free(temp);
	temp = newpath;
	return (newpath);
}

static char	*get_path(char *name, char *ENV_PATH)
{
	int		i;
	char	**paths;
	char	*newpath;

	i = 0;
	newpath = 0;
	paths = ft_split(ENV_PATH, ':');
	if (!paths)
		ft_ret_exit(1, 1);
	while (paths[i])
	{
		newpath = create_path(paths, newpath, i, name);
		if (!check_exist(newpath))
		{
			free_paths(paths);
			return (newpath);
		}
		free(newpath);
		i++;
	}
	free_paths(paths);
	return (0);
}

char	*relative_path(char *PATH, t_env *env)
{
	char	*newpath;

	newpath = get_path(PATH, search_env(env, "PATH", 4));
	if (!newpath)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": command not found", 2);
		return (NULL);
	}
	if (check_permission(newpath))
	{
		free(newpath);
		return (NULL);
	}
	return (newpath);
}
