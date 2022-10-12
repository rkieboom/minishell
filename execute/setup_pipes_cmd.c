/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 04:18:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	redirect_pipes(t_newcommand *cmd)
{
	if (cmd->id == 0) //first
	{
		
		// dup2(cmd->pipes[0], cmd->next->read_pipe);
		cmd->next->read_pipe = dup(cmd->pipes[0]);
		// close(cmd->pipes[0]);
	}
	else if (!cmd->next) //last
	{
		// close(cmd->prev->read_pipe);
	}
	else //middle
	{
		
		// dup2(cmd->pipes[0], cmd->next->read_pipe);
		cmd->next->read_pipe = dup(cmd->pipes[0]);
		// close(cmd->pipes[0]);
	}
}

void	run_pipes(t_list *list, t_newcommand *cmd)
{
	char **command;

	while (cmd)
	{
		g_global.pid = fork();
		if (g_global.pid < 0)
			ft_ret_exit(1, 1);
		else if (g_global.pid == 0)//Child execute cmd
		{
			if (setup_tokens_child(cmd))
				ft_ret_exit(1, 0);
			command = set_cmd(cmd);
			printf("\n\n-------------------ONE-------------------\n\n");
			int pid = getpid();
			char * mypid = malloc(20);   // ex. 34567
			sprintf(mypid, "lsof -p %d", pid);
			system(mypid);
			run_cmd(list, command); //probably quits after exexve
			exit(1);
			// printf("EXIT HERE\n");
			// fflush(0);
			// if (command)
			// 	free(command);
		}
		// clean_tokens_child(cmd);
		cmd = cmd->next;
	}
	wait(NULL);
	// printf("\n\n-------------------ONE-------------------\n\n");
	// int pid = getpid();
	// char * mypid = malloc(20);   // ex. 34567
	// printf(mypid, "lsof -p %d", pid);
	// system(mypid);
}

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	t_newcommand *temp = cmd;

	while (temp)
	{
		setup_pipes(temp);
		redirect_pipes(temp);
		temp = temp->next;
	}
	run_pipes(list, cmd);
	while (cmd)
	{
		clean_pipes(cmd);
		cmd = cmd->next;
	}
}
