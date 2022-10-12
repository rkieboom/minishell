/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 16:14:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 16:41:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	first(t_newcommand *cmd)
{
	if (pipe(cmd->pipes) < 0)
		ft_ret_exit(1, 1);
	cmd->next->read_pipe = dup(cmd->pipes[0]);
	close(cmd->pipes[0]);
}

static void	middle(t_newcommand *cmd)
{
	if (pipe(cmd->pipes) < 0)
		ft_ret_exit(1, 1);
	cmd->next->read_pipe = dup(cmd->pipes[0]);
		close(cmd->pipes[0]);
}

void	setup_pipes(t_newcommand *cmd)
{
	while (cmd)
	{
		if (cmd->id == 0)
			first(cmd);
		else if (!cmd->next)
			return ;
		else
			middle(cmd);
		cmd = cmd->next;
	}
}
