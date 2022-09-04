/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:17:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/04 16:08:45 by rkieboom      ########   odam.nl         */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}
