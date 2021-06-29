/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 22:47:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/06/29 16:09:56 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	pwd(t_env *v)
{
	char buf[255];
	ft_putendl_fd(getcwd(buf, 255), 1);
	// ft_putendl_fd(search_env(v, "PWD", 3), 1); //Moet getCWD worden
	return (0);
}
