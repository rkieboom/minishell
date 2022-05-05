/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:00:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/04 12:03:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static char	*get_full_env(t_env *env)
{
	int		i;
	int		j;
	int		length;
	char	*str;

	i = 0;
	j = 0;
	length = ft_strlen(env->name) + ft_strlen(env->content) + 2;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (0);
	str[length - 1] = 0;
	while (env->name[i])
	{
		str[i] = env->name[i];
		i++;
	}
	str[i] = '=';
	i++;
	while (env->content[j])
	{
		str[i + j] = env->content[j];
		j++;
	}
	return (str);
}

static char	**recreate_envp(t_env *env)
{
	char	**envp;
	t_env	*temp;
	int		length;

	length = 0;
	temp = env;
	while (temp)
	{
		length++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char *) * (length + 1));
	envp[length] = 0;
	length = 0;
	while (env)
	{
		envp[length] = get_full_env(env);
		env = env->next;
		length++;
	}
	return (envp);
}

int	is_absolute_path(char *str)
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

int	ft_execve(t_list *list, char **str)
{
	int		ret;
	char	**envp;
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_ret_exit(pid, 1);
	if (pid == 0)
	{
		envp = recreate_envp(list->env);
		if (is_absolute_path(str[0]))
			path = absolute_path(str[0]);
		else
			path = relative_path(str[0], list->env);
		if (path && execve(path, str, envp) < 0)
			ft_ret_exit(127, 1);
		else
			ft_ret_exit(1, 0);
	}	
	else
		waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	return (ret);
}
