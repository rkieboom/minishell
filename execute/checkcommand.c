/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/02/06 14:57:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	setting_pipes(t_pipe_command *s)
{
	if (s->totalcommands > 1)
	{
		if (pipe(s->newpipes) < 0)
			ft_exit(1, 1);
	}
	if (s->i == 0)
	{
		close(1);
		dup2(s->newpipes[1], 1);
	}
	else if (s->totalcommands == 1)
	{
		close(0);
		dup2(s->oldpipe, 0);
	}
	else
	{
		close(1);
		close(0);
		dup2(s->oldpipe, 0);
		dup2(s->newpipes[1], 1);
	}
}

static void clearing_pipes(t_pipe_command *s)
{
	if (s->i == 0)
	{
		close(s->newpipes[1]);
		s->oldpipe = dup(s->newpipes[0]);
		close(s->newpipes[0]);
		dup2(s->fd_stdout_cpy, 1);
		s->fd_stdout_cpy = dup(1);
	}
	else if (s->totalcommands == 1)
	{
		close(s->oldpipe);
		dup2(s->fd_stdin_cpy, 0);
		close(s->fd_stdout_cpy);
	}
	else
	{
		close(s->oldpipe);
		close(s->newpipes[1]);
		s->oldpipe = dup(s->newpipes[0]);
		close(s->newpipes[0]);
		dup2(s->fd_stdin_cpy, 0);
		dup2(s->fd_stdout_cpy, 1);
		s->fd_stdout_cpy = dup(1);
		s->fd_stdin_cpy = dup(0);
	}
}

void	exec_command_pipes(t_list *v, int k)
{
	t_pipe_command	s;

	ft_bzero(&s, sizeof(t_pipe_command));
	s.temp = v->pipecommand;
	s.fd_stdin_cpy = dup(0);
	s.fd_stdout_cpy = dup(1);
	s.totalcommands = v->tokens[k].pipe + 1;
	while (s.totalcommands)
	{
		// redirections(); //nog doen hier????
		setting_pipes(&s);
		if (command_is_builtin(s.temp->command[0]))
			execute_builtin_pipe_cmd(v, &s);
		else
			ft_execve(v, s.temp->command);
		clearing_pipes(&s);
		s.temp = s.temp->next;
		s.i++;
		s.totalcommands--;
	}
}

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
