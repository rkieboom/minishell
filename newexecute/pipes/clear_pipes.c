/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:30:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/05 13:33:10 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	clear_pipes(t_vars *vars)
{
	if (vars->i == 0)
	{
		close(vars->newpipes[1]);
		vars->oldpipes = dup(vars->newpipes[0]);
		close(vars->newpipes[0]);
		dup2(vars->fd_stdout_cpy, 1);
		vars->fd_stdout_cpy = dup(1);
	}
	else if (vars->size == 1)
	{
		close(vars->oldpipes);
		dup2(vars->fd_stdin_cpy, 0);
		close(vars->fd_stdout_cpy);
	}
	else
	{
		close(vars->oldpipes);
		close(vars->newpipes[1]);
		vars->oldpipes = dup(vars->newpipes[0]);
		close(vars->newpipes[0]);
		dup2(vars->fd_stdin_cpy, 0);
		dup2(vars->fd_stdout_cpy, 1);
		vars->fd_stdout_cpy = dup(1);
		vars->fd_stdin_cpy = dup(0);
	}
}
