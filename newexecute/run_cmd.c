/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:06:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/23 17:34:10 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
