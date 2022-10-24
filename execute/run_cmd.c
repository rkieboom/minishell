/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:34:15 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 13:51:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_cmd(t_list *list, char **cmd, int quit)
{
	if ((!cmd || !cmd[0]) && quit == 1)
		exit(0);
	else if (!cmd || !cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 5))
		g_global.status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		g_global.status = cd(list, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		g_global.status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		g_global.status = export(&list->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		g_global.status = unset(&list->env, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		g_global.status = env(list->env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else
		ft_execve(list, cmd);
	if (quit)
		exit(g_global.status);
}
