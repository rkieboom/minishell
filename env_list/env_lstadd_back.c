/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:16 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/23 01:57:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

//Adds new t_env at the back of the list
void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!temp)
		*lst = new;
	else
	{
		temp = env_lstlast(temp);
		temp->next = new;
		new->prev = temp;
	}
}
