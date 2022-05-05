/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:06:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/05 20:19:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_commands(t_list *list, t_newcommand *v)
{
	if (!ft_strncmp(v->command[0], "echo", 5))
		list->ret = echo(v->command);
	else if (!ft_strncmp(v->command[0], "cd", 3))
		list->ret = cd(list, v->command);
	else if (!ft_strncmp(v->command[0], "pwd", 4))
		list->ret = pwd();
	else if (!ft_strncmp(v->command[0], "export", 7))
		list->ret = export(list->env, v->command);
	else if (!ft_strncmp(v->command[0], "unset", 6))
		list->ret = unset(list->env, v->command);
	else if (!ft_strncmp(v->command[0], "env", 4))
		list->ret = env(list->env);
	else if (!ft_strncmp(v->command[0], "exit", 5))
		ft_exit(v->command);
	else
		list->ret = ft_execve(list, v->command);
}
