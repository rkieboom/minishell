/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_single_cmd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 00:44:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 14:04:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	is_builtin(char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

static void	setup_execve(t_list *list, t_newcommand *cmd, char **command)
{
	int	status;

	status = 0;
	g_global.pid = fork();
	if (g_global.pid < 0)
		ft_ret_exit(1, 1);
	if (g_global.pid == 0)
	{
		signals_dfl();
		env_lstadd_back(&list->env, \
		env_lst_new(ft_strdup(__DUP__), ft_strdup("")));
		if (redirections(cmd))
			ft_ret_exit(1, 0);
		run_cmd(list, command, 1);
	}
	else
		waitpid(g_global.pid, &status, 0);
	g_global.status = exit_status(status);
}

// Executes one command no Pipes
// Command is the temp command with the redirections removed as arguments
void	setup_single_cmd(t_list *list, t_newcommand *cmd)
{
	char	**command;

	command = set_cmd(cmd);
	if (is_builtin(command[0]))
		setup_builtin(list, cmd, command, tokens_exist(cmd));
	else
		setup_execve(list, cmd, command);
	if (command && tokens_exist(cmd))
		free(command);
}
