/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:06:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:32:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes/pipes.h"

void	run_cmd(t_list *list, char **cmd)
{
	if (!cmd || !cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 5))
		g_global.status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		g_global.status = cd(list, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		g_global.status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		g_global.status = export(list->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		g_global.status = unset(list->env, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		g_global.status = env(list->env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else
		g_global.status = ft_execve(list, cmd, 0);
}

void	run_cmd_redir(t_list *list, t_newcommand *v)
{
	char	**newcmd;

	if (!v->command)
		return ;
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
