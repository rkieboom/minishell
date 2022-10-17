/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 22:47:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/08 22:53:46 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	pwd(void)
{
	char	buf[4096];

	ft_putendl_fd(getcwd(buf, 4096), 1);
	return (0);
}
