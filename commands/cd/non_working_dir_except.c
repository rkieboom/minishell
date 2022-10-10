/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_working_dir_except.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:22:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/10 13:23:08 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static char	*add_path(char *str, char *path)
{
	char	*newstr;

	newstr = ft_calloc(sizeof(char), ft_strlen(str) + ft_strlen(path) + 1);
	if (!newstr)
		ft_ret_exit(1, 1);
	ft_strlcpy(newstr, str, ft_strlen(str) + 1);
	ft_strlcpy(newstr + ft_strlen(str), path, ft_strlen(path) + 1);
	return (newstr);
}

int	nonworkingdir(t_list *v, char *path)
{
	char	*newstr;

	ft_putendl_fd(\
"cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
	if (chdir(path) < 0)
		ft_ret_exit(0, 1);
	else
	{
		env_change_content(v->env, "OLDPWD", search_env(v->env, "PWD", 3));
		newstr = add_path(search_env(v->env, "PWD", 3), path);
		env_change_content(v->env, "PWD", newstr);
		free(newstr);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}
