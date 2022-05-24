/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:16:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/19 16:44:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	setup_pipes(t_vars *vars)
{
	if (vars->size > 1)
	{
		if (pipe(vars->newpipes) < 0)
			ft_ret_exit(1, 1);
	}
	if (vars->i == 0)
	{
		close(1);
		dup2(vars->newpipes[1], 1);
	}
	else if (vars->size == 1) //de laatste keer, alleen lezen uit pipes
	{
		close(0);
		dup2(vars->oldpipes, 0);
	}
	else //tussenin allebei lezen en schrijven uit pipes
	{
		close(1);
		close(0);
		dup2(vars->oldpipes, 0);
		dup2(vars->newpipes[1], 1);
	}
}