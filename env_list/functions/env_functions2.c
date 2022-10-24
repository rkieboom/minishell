/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:52:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 08:28:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"

int	env_has_data(t_env *v, char *find)
{
	while (v)
	{
		if (!ft_strncmp(v->name, find, ft_strlen(find) + 1))
		{
			if (v->content)
				return (1);
			else
				return (0);
		}
		v = v->next;
	}
	return (0);
}

int	env_exist(t_env *v, char *find)
{
	while (v)
	{
		if (!ft_strncmp(v->name, find, ft_strlen(find) + 1))
			return (1);
		v = v->next;
	}
	return (0);
}
