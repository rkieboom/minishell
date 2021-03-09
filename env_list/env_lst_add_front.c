/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_add_front.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:10:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:22:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void env_lst_add_front(s_env **lst, s_env *new)
{
	new = env_lst_new(name, content);
	new->next = *lst;
	lst = new;
}
