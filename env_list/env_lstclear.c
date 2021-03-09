/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstclear.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:23:18 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:27:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void env_lstclear(s_env **lst, void (*del)(void*))
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