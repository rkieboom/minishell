/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:06:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/19 20:39:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_cmd(t_list *list, t_newcommand *v)
{
	if (!ft_strncmp(v->command[0], "echo", 5))
		g_ret = echo(v->command);
	else if (!ft_strncmp(v->command[0], "cd", 3))
		g_ret = cd(list, v->command);
	else if (!ft_strncmp(v->command[0], "pwd", 4))
		g_ret = pwd();
	else if (!ft_strncmp(v->command[0], "export", 7))
		g_ret = export(list->env, v->command);
	else if (!ft_strncmp(v->command[0], "unset", 6))
		g_ret = unset(list->env, v->command);
	else if (!ft_strncmp(v->command[0], "env", 4))
		g_ret = env(list->env);
	else if (!ft_strncmp(v->command[0], "exit", 5))
		ft_exit(v->command);
	else
		g_ret = ft_execve(list, v->command, 0);
}
