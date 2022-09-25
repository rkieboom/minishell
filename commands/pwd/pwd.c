/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 22:47:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/22 00:16:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	pwd(void)
{
	char	buf[1024];

	ft_putendl_fd(getcwd(buf, 1024), 1);
	return (0);
}
