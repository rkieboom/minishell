/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_check_permissions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 03:19:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/18 03:19:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	cd_check_permissions(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_ret_exit(1, 2);
		ft_putendl_fd(path, 2);
		return (1);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Not a directory", 2);
		return (1);
	}
	if (!(path_stat.st_mode & X_OK))
	{
		ft_putstr_fd("minishell-4.2$: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}
