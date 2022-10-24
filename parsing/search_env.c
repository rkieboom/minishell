/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:27:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:51:55 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*search_env(t_env *v, char *name, int length, char *temp)
{
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
			if (!v->content)
				return ("");
			return (v->content);
		}
		v = v->next;
	}
	free(temp);
	return ("");
}
