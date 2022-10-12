/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_tokens_child.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:55:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 03:29:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static	void	first(t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
		close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static	void	middle()
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static	void last(t_newcommand *cmd)
{
	close(STDIN_FILENO);
	if (cmd->tokens->last_r != -1)
		close(STDOUT_FILENO);
}


void	clean_tokens_child(t_newcommand *cmd)
{
	if (cmd->id == 0)
		first(cmd);
	else if (!cmd->next)
		last(cmd);
	else
		middle();
}
