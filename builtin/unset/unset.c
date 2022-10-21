/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 20:01:05 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/19 20:28:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	remove_env(t_env *v, char *envname)
{
	t_env	*current;
	t_env	*prev;

	if (!env_exist(v, envname))
		return ;
	current = v;
	prev = v;
	while (current->next != NULL \
			&& ft_strncmp(current->name, envname, ft_strlen(envname) + 1))
	{
		prev = current;
		current = current->next;
	}
	if (!ft_strncmp(current->name, envname, ft_strlen(envname) + 1))
	{
		prev->next = prev->next->next;
		free(current->name);
		free(current->content);
		free(current);
	}
}

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (!str[i])
			return (1);
	}
	ft_putstr_fd("minishell-4.2$: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

int	unset(t_env *v, char **str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;

	while (str[i])
	{
		if (valid_identifier(str[i]))
			remove_env(v, str[i]);
		else
			error = 1;
		i++;
	}
	return (error);
}
