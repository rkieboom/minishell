/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   absolute_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:02:42 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 22:44:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

char	*absolute_path(char *PATH)
{
	if (check_exist(PATH))
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_global.status = 127;
		return (NULL);
	}
	if (check_permission(PATH))
		return (NULL);
	return (ft_strdup(PATH));
}

int	is_absolute_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
