/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 15:50:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:55:45 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_libft **alst, t_libft *new)
{
	t_libft	*nlist;

	if (!alst)
		return ;
	else if (*alst)
	{
		nlist = *alst;
		nlist = ft_lstlast(*alst);
		nlist->next = new;
		new = nlist->next;
	}
	else
		ft_lstadd_front(alst, new);
}
