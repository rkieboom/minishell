/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/17 15:50:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	checkcommand(t_list *list, int i)
{
	if (!ft_strncmp(list->cmd.cmd[i][0], "echo", 5))
		list->ret = echo(list, list->cmd.cmd[i]);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "cd", 3))
		list->ret = cd(list, list->cmd.cmd[i]);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "pwd", 4))
		list->ret = pwd(list->env);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "export", 7))
		list->ret = export(list->env, list->cmd.cmd[i]);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "unset", 6))
		list->ret = unset(list->env, list->cmd.cmd[i]);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "env", 4))
		list->ret = env(list->env);
	else if (!ft_strncmp(list->cmd.cmd[i][0], "exit", 5))
		exit(0);
	else
		list->ret = ft_execve(list, list->cmd.cmd[i]);
}
