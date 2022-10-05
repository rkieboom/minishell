/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:16:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/05 13:38:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	both(t_vars *vars)
{
	if (vars->temp->tokens->last_l < 0)
	{
		close(0);
		dup2(vars->oldpipes, 0);
		close(vars->oldpipes);
	}
	if (vars->temp->tokens->last_r < 0)
	{
		close(1);
		dup2(vars->newpipes[1], 1);
		close(vars->newpipes[1]);
	}
}

static void	setup_pipe(t_vars *vars)
{
	if (vars->size > 1)
	{
		if (pipe(vars->newpipes) < 0)
			ft_ret_exit(1, 1);
	}
}

void	setup_pipes(t_vars *vars)
{
	setup_pipe(vars);
	if (vars->i == 0)
	{
		if (vars->temp->tokens->last_r < 0)
		{
			close(1);
			dup2(vars->newpipes[1], 1);
			close(vars->newpipes[1]);
		}
	}
	else if (vars->size == 1)
	{
		if (vars->temp->tokens->last_l < 0 \
		&& vars->temp->prev->tokens->error == 0)
		{
			close(0);
			dup2(vars->oldpipes, 0);
			close(vars->oldpipes);
		}
	}
	else
		both(vars);
}
