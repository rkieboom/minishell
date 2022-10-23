/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 13:56:28 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 00:07:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>
#include <unistd.h>

//Allocate and set values
static void	set_name_value(char *envp, char **name, char **value)
{
	int		i;
	char	*result;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	result = ft_calloc(i + 1, sizeof(char));
	if (!result)
		ft_ret_exit(1, 1);
	ft_strlcpy(result, envp, i + 1);
	*name = result;
	i += 1;
	*value = ft_strdup(envp + i);
	if (!(*value))
		ft_ret_exit(1, 1);
}

//Creates the environment linked list
t_env	*create_envp(t_env *v, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (envp == 0 || !envp[0])
		return (0);
	while (envp[i])
	{
		set_name_value(envp[i], &name, &value);
		if (!v)
			v = env_lst_new(name, value);
		else
			env_lstadd_back(&v, env_lst_new(name, value));
		i++;
	}
	return (v);
}
