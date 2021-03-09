/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:04:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:07:49 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

s_list	*env_lst_new(void *name, void *content)
{
	s_list *list;

	list = malloc(sizeof(s_list));
	if (!list)
		return (NULL);
	list->name = name;
	list->content = content;
	list->next = NULL;
	return (list);
}