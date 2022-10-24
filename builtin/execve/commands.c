/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:17:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 22:44:43 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <unistd.h>

int	check_exist(char *PATH)
{
	if (access(PATH, F_OK) == 0)
		return (0);
	return (1);
}

int	check_permission(char *PATH)
{
	if (access(PATH, X_OK) != 0)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": Permission denied", 2);
		g_global.status = 126;
		return (1);
	}
	return (0);
}
