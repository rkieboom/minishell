/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 12:04:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		ft_ret_exit(1, 1);
}

void	ft_pipe(t_newcommand *temp)
{
	if (pipe(temp->fd) < 0)
		ft_ret_exit(1, 1);
}
