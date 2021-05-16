/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 13:56:28 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/16 22:49:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>
#include <unistd.h>
static void	set_name_value(char *envp, char **name, char **value)
{
	int i;
	char *result;
	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	result = malloc(i);
	if (!result)
		return ;
	ft_strlcpy(result, envp, i + 1);
	*name = result;
	i += 1;
	*value = ft_strdup(envp + i);
}
t_env	*create_envp(t_env *v, char **envp)
{
	int i;
	char *name;
	char *value;
	i = 0;
	while (envp[i])
	{
		set_name_value(envp[i], &name, &value);
		if (!v)
			v = env_lst_new(name, value);
		else
			env_lstadd_back(&v, env_lst_new(name, value));
		i++;
	}
	// print(v);
	return (v);
}

char *search_env(t_env *v, char *name, int length)
{
	while (v)
	{
		if (ft_strncmp(name, v->name, length) == 0)
			return (v->content);
		v = v->next;
	}
	return ("");
}