/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:30:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/19 16:43:31 by rkieboom      ########   odam.nl         */
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
		dup2(vars->FD_STDOUT_CPY, 1);
		vars->FD_STDOUT_CPY = dup(1);
	}
	else if (vars->size == 1) //de laatste keer, alleen lezen uit pipes
	{
		close(vars->oldpipes);
		dup2(vars->FD_STDIN_CPY, 0);
		close(vars->FD_STDOUT_CPY);
	}
	else //tussenin allebei lezen en schrijven uit pipes
	{
		close(vars->oldpipes);
		close(vars->newpipes[1]);
		vars->oldpipes = dup(vars->newpipes[0]);
		close(vars->newpipes[0]);
		dup2(vars->FD_STDIN_CPY, 0);
		dup2(vars->FD_STDOUT_CPY, 1);
		vars->FD_STDOUT_CPY = dup(1);
		vars->FD_STDIN_CPY = dup(0);
	}
}