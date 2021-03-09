/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:16:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:18:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

s_env *ft_lstlast(s_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}