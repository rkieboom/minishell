/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:16 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 14:57:54 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	temp = env_lstlast(temp);
	temp->next = new;
}
