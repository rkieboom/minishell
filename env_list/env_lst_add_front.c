/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_add_front.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 15:00:22 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 15:00:24 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void	env_lst_add_front(t_env **lst, t_env *new)
{
	new = env_lst_new(name, content);
	new->next = *lst;
	lst = new;
}
