/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 15:28:34 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 08:59:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	cpy_fds(t_list *list)
{
	list->stdin_cpy = dup(0);
	list->stdout_cpy = dup(1);
	if (list->stdin_cpy < 0 || list->stdout_cpy < 0)
		ft_ret_exit(1, 1);
}

static void	reset_fds(t_list *list, t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
		dup2(list->stdin_cpy, STDIN_FILENO);
	if (cmd->tokens->last_r != -1)
		dup2(list->stdout_cpy, STDOUT_FILENO);
	close(list->stdin_cpy);
	close(list->stdout_cpy);
}

static void	with_tokens(t_list *list, t_newcommand *cmd, char **command)
{
	cpy_fds(list);
	if (loop_over_redirs(cmd, 0, cmd->tokens->total))
	{
		reset_fds(list, cmd);
		g_global.status = 1;
		return ;
	}
	if (cmd->tokens->last_l != -1 && redir_left(cmd))
	{
		reset_fds(list, cmd);
		g_global.status = 1;
		return ;
	}
	if (cmd->tokens->last_r != -1 && redir_right(cmd))
	{
		reset_fds(list, cmd);
		g_global.status = 1;
		return ;
	}
	run_cmd(list, command, 0);
	reset_fds(list, cmd);
}

void	setup_builtin(t_list *list, \
t_newcommand *cmd, char **command, int token_exist)
{
	if (token_exist)
		with_tokens(list, cmd, command);
	else
		run_cmd(list, command, 0);
}
