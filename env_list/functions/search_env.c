/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:47:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/03 12:19:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>

static t_env	*search_envname(t_env *v, char *envname)
{
	while (v)
	{
		if (ft_strncmp(v->name, envname, ft_strlen(envname) + 1) == 0)
			return (v);
		v = v->next;
	}
	return (NULL);
}

void	env_change_content(t_env *v, char *envname, char *envcontent)
{
	v = search_envname(v, envname);
	if (v)
	{
		free(v->content);
		v->content = ft_strdup(envcontent);
	}
}

char	*search_env(t_env *v, char *name, int length)
{
	char	*temp;

	if (length == 0)
	{
		if (*name == '$')
			name++;
		while (name[length] && (ft_isdigit(name[length]) || \
				ft_isalpha(name[length]) || (name[length] == '_')))
			length++;
	}
	temp = ft_substr(name, 0, length);
	if (!temp)
		ft_ret_exit(1, 1);
	while (v)
	{
		if (ft_strncmp(temp, v->name, length + 1) == 0)
		{
			free(temp);
			return (v->content);
		}
		v = v->next;
	}
	free(temp);
	return ("");
}

char	*search_envname_returnenvname(t_env *v, char *envname)
{
	while (v)
	{
		if (ft_strncmp(v->name, envname, ft_strlen(envname) + 1) == 0)
			return (v->name);
		v = v->next;
	}
	return ("");
}
