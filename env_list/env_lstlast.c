/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:52:36 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 14:52:47 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

t_env	*env_lstlast(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
