/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstsize.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:52:07 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 14:52:17 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
