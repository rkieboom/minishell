/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 14:24:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/11/15 20:20:03 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_libft *lst)
{
	int result;

	result = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		result++;
		lst = lst->next;
	}
	return (result);
}
