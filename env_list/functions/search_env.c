/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:47:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/24 21:23:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>

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
	if (length == 0)
	{
		if (*name == '$')
			name++;
		while (name[length] && (ft_isdigit(name[length]) || \
				ft_isalpha(name[length]) || (name[length] == '_')))
			length++;
	}
	while (v)
	{
		if (ft_strncmp(name, v->name, length) == 0 && v->name[length] == '\0')
			return (v->content);
		v = v->next;
	}
	return ("");
}

t_env	*search_envname(t_env *v, char *envname)
{
	while (v)
	{
		if (ft_strncmp(v->name, envname, ft_strlen(envname)) == 0)
			return (v);
		v = v->next;
	}
	return (NULL);
}

char	*search_envname_returnenvname(t_env *v, char *envname)
{
	while (v)
	{
		if (ft_strncmp(v->name, envname, ft_strlen(envname)) == 0)
			return (v->name);
		v = v->next;
	}
	return ("");
}
