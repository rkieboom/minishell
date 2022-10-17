/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:00:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 14:10:52 by rkieboom      ########   odam.nl         */
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
	str = ft_calloc(length, sizeof(char));
	if (!str)
		ft_ret_exit(1, 1);
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
	envp = ft_calloc(length + 1, sizeof(char *));
	if (!envp)
		ft_ret_exit(1, 1);
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

static void	run_child(t_list *list, char **str)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = recreate_envp(list->env);
	if (is_absolute_path(str[0]))
		path = absolute_path(str[0]);
	else
		path = relative_path(str[0], list->env);
	if (path && execve(path, str, envp) < 0)
		ft_ret_exit(1, 1);
	else
		ft_ret_exit(127, 0);
}

void	ft_execve(t_list *list, char **str)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	run_child(list, str);
}
