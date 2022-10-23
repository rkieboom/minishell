/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:58 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/23 00:07:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

//Create new t_env object
t_env	*env_lst_new(void *name, void *content)
{
	t_env	*list;

	list = ft_calloc(1, sizeof(t_env));
	if (!list)
		return (NULL);
	list->name = name;
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
