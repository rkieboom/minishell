/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstclear.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:06 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 14:59:32 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void	env_lstclear(t_env **lst, void (*del)(void*))
{
	if (!lst)
		return ;
	while (lst->next)
	{
		temp = *lst->next;
		free(*lst);
		*lst = temp;
	}
}
