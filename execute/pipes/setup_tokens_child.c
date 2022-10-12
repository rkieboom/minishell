/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_tokens_child.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:55:51 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 04:20:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static	int	first(t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
	{
		if (redir_left(cmd))
			return (1);
	}
	// close(cmd->pipes[0]);
	dup2(cmd->pipes[1], STDOUT_FILENO);
	// close(cmd->pipes[1]);
	return (0);
}

static	int	middle(t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
	{
		if (redir_left(cmd))
			return (1);
	}
	else
		dup2(cmd->read_pipe, STDIN_FILENO);
	// close(cmd->read_pipe);
	
	// close(cmd->pipes[0]);
	dup2(cmd->pipes[1], STDOUT_FILENO);
	// close(cmd->pipes[1]);
	return (0);
}

static	int last(t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
	{
		if (redir_left(cmd))
			return (1);
	}
	else
	{
		dup2(cmd->read_pipe, STDIN_FILENO);
		// close(cm`1d->read_pipe);
	}
	if (cmd->tokens->last_r != -1)
		redir_right(cmd);
	return (0);
}


int	setup_tokens_child(t_newcommand *cmd)
{
	if (loop_over_redirs(cmd, 0, cmd->tokens->total))
		return (1);
	if (cmd->id == 0)
	{
		printf("IN FIRST\n");
		fflush(0);
		if (first(cmd))
			return (1);
	}
	else if (!cmd->next)
	{
		printf("IN LAST\n");
		fflush(0);
		if (last(cmd))
			return (1);
	}
	else
	{
		printf("IN MIDf\n");
		fflush(0);
		if (middle(cmd))
			return (1);
	}
	return (0);
}
