/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 13:56:28 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 15:47:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../env_list.h"
#include <stdio.h>

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

static void print(t_env *v)
{
	while (v)
	{
		printf("%s=%s\n", v->name, v->content);
		v = v->next;
	}
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