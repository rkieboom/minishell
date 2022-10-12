/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:45:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 15:36:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	first(t_newcommand *cmd)
{
	// dup2(cmd->pipes[0], cmd->next->read_pipe);
	close(cmd->pipes[0]);
	close(cmd->pipes[1]);
}

static void	middle(t_newcommand *cmd)
{
	// dup2(cmd->pipes[0], cmd->next->read_pipe);
	close(cmd->pipes[0]);
	close(cmd->pipes[1]);
	close(cmd->read_pipe);
}

static void	last(t_newcommand *cmd)
{
	close(cmd->read_pipe);
}

void	clean_pipes(t_newcommand *cmd)
{
	while (cmd)
	{
		if (cmd->id == 0)
			first(cmd);
		else if (!cmd->next)
			last(cmd);
		else
			middle(cmd);
		cmd = cmd->next;
	}
}
