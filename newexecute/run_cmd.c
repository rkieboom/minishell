/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:06:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/28 14:52:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes/pipes.h"

static void	go(t_list *list, t_newcommand *cmd, char **newcmd)
{
	t_heredoc_data	*data;

	data = cmd->tokens->heredoc->data;
	while (data)
	{
		set_pipe_heredoc(cmd->tokens->heredoc, data);
		if (!redirections(list, cmd))
		{
			run_cmd(list, newcmd);
			if (write(1, "\n", 1) < 0)
				ft_ret_exit(1, 1);
		}
		reset_redirections(list, cmd);
		clear_pipe_heredoc(cmd->tokens->heredoc);
		data = data->next;
	}
}

void	run_cmd_heredoc(t_list *list, t_newcommand *cmd)
{
	char	**newcmd;

	newcmd = set_cmd(cmd);
	if (!newcmd)
		ft_ret_exit(1, 0);
	if (!newcmd[0])
	{
		free(newcmd);
		return ;
	}
	go(list, cmd, newcmd);
	free(newcmd);
}

void	run_cmd(t_list *list, char **cmd)
{
	if (!cmd || !cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 5))
		g_ret = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		g_ret = cd(list, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		g_ret = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		g_ret = export(list->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		g_ret = unset(list->env, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		g_ret = env(list->env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else
		g_ret = ft_execve(list, cmd, 0);
}

void	run_cmd_redir(t_list *list, t_newcommand *v)
{
	char	**newcmd;

	newcmd = set_cmd(v);
	if (!newcmd[0])
	{
		free(newcmd);
		return ;
	}
	run_cmd(list, newcmd);
	if (v->tokens && v->tokens->total > 0)
		free(newcmd);
}
