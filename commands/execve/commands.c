/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:17:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/07 12:18:03 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int check_exist(char *PATH)
{
	int fd;

	fd = open(PATH, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	check_permission(char *PATH)
{
	struct stat stats;

	if (stat(PATH, &stats) != 0)
		return (1);
	else if (!(stats.st_mode & X_OK))
		return (1);
	
	return (0);
}