/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 14:33:15 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/11/15 20:20:03 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libft	*ft_lstlast(t_libft *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
