/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:19:01 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:32:48 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void env_lstadd_back(s_env **lst, s_env *new)
{
	s_env *temp;
	temp = *lst;
	temp = env_lstlast(temp);
	temp->next = new;
}
