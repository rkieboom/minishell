/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:58 by spelle        #+#    #+#                 */
/*   Updated: 2021/03/09 14:56:55 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

t_env	*env_lst_new(void *name, void *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->name = name;
	list->content = content;
	list->next = NULL;
	return (list);
}
