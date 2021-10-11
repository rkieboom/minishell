/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:17:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/11 15:46:25 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	check_exist(char *PATH)
{
	struct stat	stats;
	int			fd;

	fd = open(PATH, O_RDONLY);
	if (fd < 0)
	{
		if (stat(PATH, &stats) == 0)
			return (0);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_permission(char *PATH)
{
	struct stat	stats;

	if (stat(PATH, &stats) != 0)
		return (1);
	else if (!(stats.st_mode & X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}
