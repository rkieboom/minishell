/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:00:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/16 17:40:23 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

static char *get_full_env(t_env *env)
{
	int i;
	int j;
	int length;
	char *str;

	i = 0;
	j = 0;
	length = ft_strlen(env->name) + ft_strlen(env->content) + 2;
	str = malloc(sizeof(char) * length);
	str[length] = 0;
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

static char **recreate_envp(t_env *env)
{
	char **envp;
	t_env *temp;
	int length;

	length = 0;
	temp = env;
	while (temp)
	{
		length++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char **) * (length + 1));
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

void	free_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int ft_execve(t_list *list, char **str)
{
	int result;
	char **envp;
	char *path;
	int	i;

	i = 0;
	envp = recreate_envp(list->env);
	if (str[0] && str[0][0] == '.' && str[0][1] == '/')
		path = relative_path(str[0]);
	else
		path = absolute_path(str[0], list->env);
	if (path)
		result = execve(path, str, envp);
	// printf("%s", strerror(errno));
	fflush(NULL);
	return (0);
}

