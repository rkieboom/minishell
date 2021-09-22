/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 20:01:05 by spelle        #+#    #+#                 */
/*   Updated: 2021/09/21 14:55:50 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	remove_env(t_env *v, char *envname)
{
	t_env	*prev;
	t_env	*current;

	prev = v;
	current = v;
	while (current->next != NULL \
			&& ft_strncmp(current->name, envname, ft_strlen(envname)))
	{
		prev = current;
		current = current->next;
	}
	if (!ft_strncmp(current->name, envname, ft_strlen(envname)))
	{
		prev->next = prev->next->next;
		free(current->name);
		free(current->content);
		free(current);
	}
}

int	unset(t_env *v, char **str)
{
	int		i;

	if (str[1] == NULL)
		return (0);
	i = 1;
	while (str[i] != NULL)
	{
		if (!ft_strncmp(search_envname_returnenvname(v, str[i]), "", 1))
			ft_putstr_fd("", 1);
		else
			remove_env(v, str[i]);
		i++;
	}
	return (0);
}
