/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/21 13:54:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static void	close_all_fds(t_newcommand *cmd)
// {
// 	while (cmd)
// 	{
// 		if (cmd->fd[0] != 0)
// 		{
// 			close(cmd->fd[0]);
// 		}
// 		// if (cmd->fd[1] != 1 && cmd->next)
// 		// {
// 		// 	close(cmd->fd[1]);
// 		// }
// 		cmd = cmd->next;
// 	}
// }

// static void	init_fd(t_newcommand *cmd)
// {
// 	cmd->fd[0] = 0;
// 	cmd->fd[1] = 1;
// }

// void	setup_pipe_stuff(t_newcommand *cmd)
// {
// 	int	pip[2];
// 	int	save;

// 	// signal(SIGCHLD, SIG_IGN);
// 	save = 0;
// 	while (cmd)
// 	{
// 		init_fd(cmd);
// 		if (pipe(pip) < 0)
// 			ft_ret_exit(1, 1);
// 		cmd->fd[0] = save;
// 		save = pip[0];
// 		if (cmd->next)
// 			cmd->fd[1] = pip[1];
// 		else
// 			close(pip[1]);
// 		cmd = cmd->next;
// 	}
// }

// static void	child(t_list *list, t_newcommand *cmd)
// {
// 	char	**command;

// 	command = set_cmd(cmd);
// 	if (loop_over_redirs(cmd, 0, cmd->tokens->total))
// 		exit(1);

// 	dprintf(2, "CMD = %s\nPIP0=%i\nPIP1=%i\n\n", command[0], cmd->fd[0], cmd->fd[1]);
// 	if (cmd->fd[0] != 0)
// 	{
// 		dup2(cmd->fd[0], 0);
// 		close(cmd->fd[0]);
// 	}
// 	// else
// 	// 	close(cmd->fd[0]);//IDK
// 	if (cmd->fd[1] != 1)
// 	{
// 		dup2(cmd->fd[1], 1);
// 		close(cmd->fd[1]);
// 	}
// 	// else if (!cmd->next && cmd->tokens->last_r != -1)
// 	// 	redir_right(cmd);
// 	// else
// 	// 	close(cmd->fd[1]);
// 	// if (cmd->tokens->last_l != -1)
// 	// 	if (redir_left(cmd))
// 	// 		exit(1);
// 	close_all_fds(cmd);
// 	run_cmd(list, command);
// }

// static void	last(t_list *list, t_newcommand *cmd)
// {
// 	char	**command;

// 	command = set_cmd(cmd);
// 	if (cmd->fd[0] != -1)
// 	{
// 		dup2(cmd->fd[0], 0);
// 		close(cmd->fd[0]);
// 	}
// 	run_cmd(list, command);
// }

// static void	run_pipes(t_list *list, t_newcommand *cmd, int status)
// {
// 	pid_t	pid;

// 	if (!cmd)
// 		return ;
// 	pid = fork();
// 	if (pid < 0)
// 		ft_ret_exit(1, 1);
// 	else if (pid == 0)
// 		child(list, cmd);
// 	else
// 	{
// 		printf("Pid = %i\n", pid);
// 		// close(cmd->fd[0]);//Weghalen??
// 		close(cmd->fd[1]);
// 		if (cmd)
// 			run_pipes(list, cmd->next, status);
// 		// else
// 		// 	last(list, cmd);
// 	}
// 	close(STDIN_FILENO);
// 	waitpid(pid, 0, 0);
// 	// wait(NULL);
// }

// void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	status = 0;
// 	pid = fork();
// 	if (pid < 0)
// 		ft_ret_exit(1, 1);
// 	else if (pid == 0)
// 	{
// 		dprintf(2, "Setting up Pipes\n");
// 		setup_pipe_stuff(cmd);
// 		dprintf(2, "Running up Pipes\n");
// 		run_pipes(list, cmd, status);
// 		dprintf(2, "Exiting Pipes\n");
// 		exit(exit_status(status));
// 	}
// 	else
// 	{
// 		dprintf(2, "Special pid = %i\n", pid);
// 		waitpid(pid, &status, 0);
// 		// sleep(1);
// 		// rl_redisplay();
// 	}
// 	g_global.status = exit_status(status);
// }

// static void	new_run_pipes(t_list *list, t_newcommand *cmd)
// {
// 	pid_t	pid;

// 	if (!cmd)
// 		return ;
// 	pid = fork();
// 	if (pid < 0)
// 		ft_ret_exit(1, 1);
// 	else if (pid == 0)
// 		child(list, cmd);
// 	else
// 	{
// 		printf("Pid = %i\n", pid);
// 		// close(cmd->fd[0]);//Weghalen??
// 		// if (cmd->next)
// 		// 	close(cmd->fd[1]);
// 		// close(cmd->fd[0]);
// 		// if (cmd)
// 		// run_pipes(list, cmd->next, status);
// 		// else
// 		// 	last(list, cmd);
// 	}
// 	// close(STDIN_FILENO);
// 	// waitpid(pid, 0, 0);
// 	// wait(NULL);
// }

// static void clean_pipes(t_newcommand *cmd)
// {
// 	while (cmd)
// 	{
// 		close(cmd->fd[0]);
// 		if (cmd->next)
// 			close(cmd->fd[1]);
// 		cmd = cmd->next;
// 	}
// }

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	int	pid;
	int	fd[2];
	t_newcommand *temp = cmd;
	int	fd_read = dup(0);

	
	while (temp)
	{
		if (temp->next)
		{
			pipe(fd);
			pid = fork();
			if (!pid)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
				
				//exec shit
				dup2(fd_read, 0);
				close(fd_read);
				run_cmd(list, temp->command);
			}
			else
			{
				close(fd[1]);
				close(fd_read);
				fd_read = fd[0];
			}
		}
		else if (!temp->next)
		{
			pid = fork();
			if (!pid)
			{
				dup2(fd_read, 0);
				close(fd_read);
				run_cmd(list, temp->command);
			}
			else
			{
				close(fd_read);
				while (waitpid(-1, 0, WUNTRACED) != -1);
			}
		}
		temp = temp->next;
	}









	
	// t_newcommand *temp = cmd;
	// int fd_cpy[2];

	// fd_cpy[0] = dup(0);
	// fd_cpy[1] = dup(1);

	// setup_pipe_stuff(cmd);
	// pid_t pid = fork();
	// if (pid < 0)
	// 	ft_ret_exit(1, 1);
	// else if (pid == 0)
	// {
		// while (temp)
		// {
		// 	new_run_pipes(list, temp);
		// 	temp = temp->next;
		// 	// close(temp->fd[1]);
		// }
	// while (waitpid(-1, 0, WUNTRACED) != -1);
		// while (wait(NULL) != -1);
		// exit(0);
	// temp = cmd;
	// }
	// else
	// {
	// 	dprintf(2, "Lastpid CMD = %i\n", pid);
	// 	waitpid(pid, 0, 0);
	// }
	// close_all_fds(temp);
	// dup2(fd_cpy[0], 0);
	// dup2(fd_cpy[1], 1);
	// close(fd_cpy[0]);
	// close(fd_cpy[1]);
}
