/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:47:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/19 11:20:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"

char *search_env(t_env *v, char *name, int length)
{
	if (length == 0)
	{
		if (*name == '$')
			name++;
		while (name[length] && (ft_isdigit(name[length]) || ft_isalpha(name[length])))
			length++;
	}
	while (v)
	{
		if (ft_strncmp(name, v->name, length) == 0)
			return (v->content);
		v = v->next;
	}
	return ("");
}
