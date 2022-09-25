/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:16:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/21 04:13:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	both(t_vars *vars)
{
	if (vars->temp->tokens->last_l < 0)
	{
		close(0);
		dup2(vars->oldpipes, 0);
	}
	if (vars->temp->tokens->last_r < 0)
	{
		close(1);
		dup2(vars->newpipes[1], 1);
	}
}

void	setup_pipes(t_vars *vars)
{
	if (vars->size > 1)
	{
		if (pipe(vars->newpipes) < 0)
			ft_ret_exit(1, 1);
	}
	if (vars->i == 0)
	{
		if (vars->temp->tokens->last_r < 0)
		{
			close(1);
			dup2(vars->newpipes[1], 1);
		}
	}
	else if (vars->size == 1)
	{
		if (vars->temp->tokens->last_l < 0)
		{
			close(0);
			dup2(vars->oldpipes, 0);
		}
	}
	else
		both(vars);
}
