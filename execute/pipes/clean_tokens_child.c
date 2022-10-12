/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_tokens_child.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:55:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 16:58:38 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static	void	first(t_list *list, t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
	{
		dup2(list->stdin_cpy, STDIN_FILENO);
		close(list->stdin_cpy);
	}
	dup2(list->stdout_cpy, STDOUT_FILENO);
	close(list->stdout_cpy);
}

static	void	middle(t_list *list)
{
	dup2(list->stdin_cpy, STDIN_FILENO);
	dup2(list->stdout_cpy, STDOUT_FILENO);
	close(list->stdin_cpy);
	close(list->stdout_cpy);
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
}

static	void last(t_list *list, t_newcommand *cmd)
{
	dup2(list->stdin_cpy, STDIN_FILENO);
	close(list->stdin_cpy);
	// close(STDIN_FILENO);
	if (cmd->tokens->last_r != -1)
	{
		dup2(list->stdout_cpy, STDOUT_FILENO);
		close(list->stdout_cpy);
	}
		// close(STDOUT_FILENO);
}

void	clean_tokens_child(t_list *list, t_newcommand *cmd)
{
	(void)list;

	if (cmd->id == 0)
	{
		dprintf(2, "IN FIRST CLOSING\n");
		fflush(0);
		first(list, cmd);
	}
	else if (!cmd->next)
	{
		dprintf(2, "IN LAST CLOSING\n");
		fflush(0);
		last(list, cmd);
	}
	else
	{
		dprintf(2, "IN MID CLOSING\n");
		fflush(0);
		middle(list);
	}
}
