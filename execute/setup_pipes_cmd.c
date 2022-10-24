/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:00:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	get_cmd_len(t_newcommand *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static void	start_commands(t_list *list, t_newcommand *temp, pid_t *pids, int i)
{
	temp->read_pipe = dup(0);
	while (temp->next)
	{
		pipe(temp->fd);
		pids[i] = fork();
		if (!pids[i])
		{
			signals_dfl();
			// Setup writing pipe
			dup2(temp->fd[1], STDOUT_FILENO);
			close(temp->fd[1]);
			close(temp->fd[0]);
			
			//Setup reading from pipe
			dup2(temp->read_pipe, 0);
			close(temp->read_pipe);

			if (loop_over_redirs(temp, 0, temp->tokens->total))
				ft_ret_exit(1, 0);
			if (temp->tokens->last_l != -1)
			{
				if (redir_left(temp))
					ft_ret_exit(1, 0);
			}
			if (temp->tokens->last_r != -1)
			{
				if (redir_right(temp))
					ft_ret_exit(1, 0);
			}
			run_cmd(list, set_cmd(temp), 1);
		}
		else
		{
			i++;
			close(temp->fd[1]);
			close(temp->read_pipe);
			temp->next->read_pipe = temp->fd[0];
		}
		temp = temp->next;
	}
}

static int	last_command(t_list *list, t_newcommand *temp, pid_t *pids, int len)
{
	int	status;
	int	i;

	i = 0;
	while (temp->next)
		temp = temp->next;
	pids[len] = fork();
	if (!pids[len])
	{
		signals_dfl();
		dup2(temp->read_pipe, 0);
		close(temp->read_pipe);
		run_cmd(list, set_cmd(temp), 1);
	}
	else
	{
		close(temp->read_pipe);
		while (i < (len + 1))
		{
			waitpid(pids[i], &status, WUNTRACED);
			i++;
		}
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (1);
}

//Multiple commands with Pipes execution
void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	pid_t		*pids;
	const int	len = get_cmd_len(cmd);

	pids = ft_calloc(len, sizeof(pid_t));
	if (!pids)
		ft_ret_exit(1, 1);
	start_commands(list, cmd, pids, 0);
	g_global.status = last_command(list, cmd, pids, len - 1);
}
