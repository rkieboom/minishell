/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 12:26:36 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	init_fd(t_newcommand *cmd)
{
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
}

void			setup_pipe_stuff(t_newcommand *cmd)
{
	int	pip[2];
	int	save = 0;

	while (cmd)
	{
		init_fd(cmd);
		if (pipe(pip) < 0)
			ft_ret_exit(1, 1);
		cmd->fd[0] = save;
		save = pip[0];
		if (cmd->next)
			cmd->fd[1] = pip[1];
		else
			close(pip[1]);
		cmd = cmd->next;
	}
}

static void	child(t_list *list, t_newcommand *cmd)
{
	char **command;

	command = set_cmd(cmd);
	if (loop_over_redirs(cmd, 0, cmd->tokens->total))
		exit(1);
	if (cmd->fd[0] != 0)
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
	if (cmd->fd[1] != 1)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
	}
	else if (!cmd->next && cmd->tokens->last_r != -1)
		redir_right(cmd);
	if (cmd->tokens->last_l != -1) //one way to do it
		if (redir_left(cmd))
			exit(1);
	run_cmd(list, command);
}

static void	run_pipes(t_list *list, t_newcommand *cmd, int status)
{
	pid_t	pid;

	if (!cmd)
		return ;
	pid = fork();
	if (pid < 0)
		ft_ret_exit(1, 1);
	else if (pid == 0)
		child(list, cmd);
	else
	{
		close(cmd->fd[1]);
		if (cmd)
			run_pipes(list, cmd->next, status);
	}
	close(STDIN_FILENO);
	wait(&status);
}

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		ft_ret_exit(1, 1);
	else if (pid == 0)
	{
		setup_pipe_stuff(cmd);
		run_pipes(list, cmd, status);
		exit(exit_status(status));
	}
	else
		waitpid(-1, &status, 0);
	g_global.status = exit_status(status);
}
