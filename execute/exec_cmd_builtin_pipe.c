/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd_builtin_pipe.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/30 14:53:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/02/06 14:19:10 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	command_is_builtin(char *str)
{
	if (!ft_strncmp("cd", str, 3))
		return (1);
	else if (!ft_strncmp("echo", str, 5))
		return (1);
	else if (!ft_strncmp("env", str, 4))
		return (1);
	else if (!ft_strncmp("exit", str, 5))
		return (1);
	else if (!ft_strncmp("export", str, 7))
		return (1);
	else if (!strncmp("pwd", str, 4))
		return (1);
	else if (!strncmp("unset", str, 6))
		return (1);
	return (0);
}

void	execute_builtin_pipe_cmd(t_list *v, t_pipe_command *cmd)
{
	if (!ft_strncmp("cd", cmd->temp->command[0], 3))
		cd(v, cmd->temp->command);
	else if (!ft_strncmp("echo", cmd->temp->command[0], 5))
		echo(v, cmd->temp->command);
	else if (!ft_strncmp("env", cmd->temp->command[0], 4))
		env(v->env);
	else if (!ft_strncmp("exit", cmd->temp->command[0], 5))
		exit(ft_atoi(cmd->temp->command[0]));
	else if (!ft_strncmp("export", cmd->temp->command[0], 7))
		export(v->env, cmd->temp->command);
	else if (!strncmp("pwd", cmd->temp->command[0], 4))
		pwd(v->env);
	else if (!strncmp("unset", cmd->temp->command[0], 6))
		unset(v->env, cmd->temp->command);
}
