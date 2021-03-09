/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/29 07:25:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:55:38 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_libft **lst, void (*del)(void*))
{
	t_libft	*temp;
	t_libft	*list;

	list = *lst;
	while (list)
	{
		ft_lstdelone(list, del);
		temp = list->next;
		list = temp;
	}
	*lst = NULL;
}
