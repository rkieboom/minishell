/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/22 13:43:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	start_commands(t_list *list, t_newcommand *temp)
{
	temp->read_pipe = dup(0);
	while (temp->next)
	{
		pipe(temp->fd);
		g_global.pid = fork();
		if (!g_global.pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			// Setup writing pipe
			dup2(temp->fd[1], STDOUT_FILENO);
			close(temp->fd[1]);
			close(temp->fd[0]);
			
			//Setup reading from pipe
			dup2(temp->read_pipe, 0);
			close(temp->read_pipe);
			run_cmd(list, set_cmd(temp));
		}
		else
		{
			close(temp->fd[1]);
			close(temp->read_pipe);
			temp->next->read_pipe = temp->fd[0];
		}
		temp = temp->next;
	}
}

static int	last_command(t_list *list, t_newcommand *temp)
{
	int	status;

	while (temp->next)
		temp = temp->next;
	g_global.pid = fork();
	if (!g_global.pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(temp->read_pipe, 0);
		close(temp->read_pipe);
		run_cmd(list, set_cmd(temp));
	}
	else
	{
		close(temp->read_pipe);
		while (waitpid(-1, &status, WUNTRACED) != -1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (1);
}

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	start_commands(list, cmd);
	g_global.status = last_command(list, cmd);
}
