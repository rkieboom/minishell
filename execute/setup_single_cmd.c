/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_single_cmd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 00:44:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:00:13 by rkieboom      ########   odam.nl         */
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

static int	tokens_exist(t_newcommand *cmd)
{
	if (cmd->tokens && cmd->tokens->total > 0)
		return (1);
	else
		return (0);
}

static void	setup_execve(t_list *list, t_newcommand *cmd, char **command)
{
	int	status;

	status = 0;
	g_global.pid = fork();
	if (g_global.pid == 0)
	{
		signals_dfl();
		env_lstadd_back(&list->env, env_lst_new(ft_strdup(__DUP__), ft_strdup("")));
		if (tokens_exist(cmd) && loop_over_redirs(cmd, 0, cmd->tokens->total))
			ft_ret_exit(1, 0);
		if (tokens_exist(cmd) && cmd->tokens->last_l != -1)
		{
			if (redir_left(cmd))
				ft_ret_exit(1, 0);
		}
		if (tokens_exist(cmd) && cmd->tokens->last_r != -1)
			redir_right(cmd);
		run_cmd(list, command, 1);
	}
	else
		waitpid(g_global.pid, &status, 0);
	g_global.status = exit_status(status);
}

//Executes one command no Pipes
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
