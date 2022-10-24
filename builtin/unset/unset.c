/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 20:01:05 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/23 22:51:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if ((ft_isalpha(str[0]) || str[0] == '_') && ft_strncmp(str, "", 1) != 0)
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

int	unset(t_env **v, char **str)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (str[i])
	{
		if (valid_identifier(str[i]))
			env_lst_remove(v, str[i]);
		else
			error = 1;
		i++;
	}
	return (error);
}
