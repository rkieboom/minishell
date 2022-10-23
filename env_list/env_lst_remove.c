/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_remove.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 17:40:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 02:00:08 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

// void	env_lst_remove(t_env **v, char *find)
// {
// 	t_env	*current;
// 	t_env	*prev;
// 	int		i = 0;

// 	if (!env_exist(v, find))
// 		return ;
// 	current = v;
// 	prev = v;
// 	while (current->next != NULL \
// 			&& ft_strncmp(current->name, envname, ft_strlen(envname) + 1))
// 	{
// 		prev = current;
// 		current = current->next;
// 		i++;
// 	}
// 	if (!ft_strncmp(current->name, envname, ft_strlen(envname) + 1))
// 	{
// 		if (i == 0)
// 			*v = prev->next;
// 		prev->next = prev->next->next;
// 		free(current->name);
// 		free(current->content);
// 		free(current);
// 	}
// }

void	env_lst_remove(t_env **v, char *find)
{
	t_env	*cur;

	cur = env_get(*v, find);
	if (!cur)
		return ;
	if (!cur->prev)
	{
		*v = cur->next;
		if (cur->next)
			cur->next->prev = 0;
		free(cur->name);
		free(cur->content);
		free(cur);
	}
	else
	{
		cur->prev->next = cur->next;
		if (cur->next)
			cur->next->prev = cur->prev;
		free(cur->name);
		free(cur->content);
		free(cur);
	}
}
