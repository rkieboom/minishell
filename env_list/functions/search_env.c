/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:47:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 12:47:42 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"

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
