/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 20:38:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	*init_pip(void)
{
	int *n;

	n = ft_calloc(2, sizeof(int));
	if (!n)
		ft_ret_exit(1, 1);
	n[0] = 0;
	n[1] = 1;
	return n;
}

static void	exec_cmd(t_list *list, t_newcommand *cmd)
{
	g_global.pid = fork();
	if (g_global.pid < 0)
		ft_ret_exit(1, 1);
	else if (g_global.pid == 0)
	{
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
		ft_execve(list, cmd->command);
	}
	close(cmd->fd[1]);
}

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	(void)list;
	int	pip[2];
	int save = 0;
	t_newcommand *temp = cmd;

	int pid;

	pid = fork();
	if (pid == 0)
	{
		while (temp)
		{
			temp->fd = init_pip();
			if (pipe(pip) < 0)
				ft_ret_exit(1, 1);
			temp->fd[0] = save;
			save = pip[0];
			if (temp->next)
				temp->fd[1] = pip[1];
			else
				close(pip[1]);
			temp = temp->next;
		}
		temp = cmd;
		while (temp->next)
		{
			exec_cmd(list, temp);
			temp = temp->next;
		}
		if (temp->fd[0] != 0)
			dup2(temp->fd[0], 0);
		exec_cmd(list, temp);
	}
	else
		waitpid(pid, 0, 0);
	// waitpid(g_global.pid, 0, 0);
	// wait(NULL);
	
	// if (dup2(stdin, 0) < 0)
	// 	ft_ret_exit(1, 1);
	// if (dup2(stdout, 1) < 0)
	// 	ft_ret_exit(1, 1);
}
