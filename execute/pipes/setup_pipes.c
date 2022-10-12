/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 16:14:11 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/11 22:52:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	first(t_newcommand *cmd)
{
	//cant read, its the first command.
	//has to write to out
	if (pipe(cmd->pipes) < 0)
		ft_ret_exit(1, 1);
}

static void	middle(t_newcommand *cmd)
{
	//only read if there is no left redir
	//it does write to pipe even if there is a right redir
	if (pipe(cmd->pipes) < 0)
		ft_ret_exit(1, 1);
}

	//LAST
	//only read if there is no left redir


void	setup_pipes(t_newcommand *cmd)
{
	if (cmd->id == 0)
		first(cmd);
	else if (!cmd->next)
		return ;
	else
		middle(cmd);
}
