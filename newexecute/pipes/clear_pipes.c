/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:30:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:09:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	both(t_vars *vars)
{
	close(vars->oldpipes);
	close(vars->newpipes[1]);
	vars->oldpipes = dup(vars->newpipes[0]);
	close(vars->newpipes[0]);
	if (vars->temp->tokens->last_l < 0)
		dup2(vars->fd_stdin_cpy, 0);
	if (vars->temp->tokens->last_r < 0)
		dup2(vars->fd_stdout_cpy, 1);
}

void	clear_pipes(t_vars *vars)
{
	if (vars->i == 0)
	{
		close(vars->newpipes[1]);
		vars->oldpipes = dup(vars->newpipes[0]);
		close(vars->newpipes[0]);
		if (vars->temp->tokens->last_r < 0)
			dup2(vars->fd_stdout_cpy, 1);
	}
	else if (vars->size == 1)
	{
		close(vars->oldpipes);
		if (vars->temp->tokens->last_l < 0)
			dup2(vars->fd_stdin_cpy, 0);
	}
	else
		both(vars);
}
