/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 17:02:18 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_pipes(t_list *list, t_newcommand *cmd)
{
	char **command;

	// while (cmd)
	// {
		g_global.pid = fork();
		if (g_global.pid < 0)
			ft_ret_exit(1, 1);
		else if (g_global.pid == 0)//Child execute cmd
		{
			if (setup_tokens_child(list, cmd))
				return ;
			command = set_cmd(cmd);
			// printf("\n\n-------------------ONE-------------------\n\n");
			// int pid = getpid();
			// char * mypid = malloc(20);   // ex. 34567
			// sprintf(mypid, "lsof -p %d", pid);
			// system(mypid);
			dprintf(2, "IN CMD %s\n", command[0]);
			run_cmd(list, command); //probably quits after exexve
			dprintf(2, "EXIT CMD %s\n", command[0]);
			exit(1);
			// printf("EXIT HERE\n");
			// fflush(0);
			// if (command)
			// 	free(command);
		// }
		// 	clean_tokens_child(list, cmd);
		// clean_tokens_child(list, cmd);
		// cmd = cmd->next;
	}
	// wait(NULL);
	// printf("\n\n-------------------ONE-------------------\n\n");
	// int pid = getpid();
	// char * mypid = malloc(20);   // ex. 34567
	// printf(mypid, "lsof -p %d", pid);
	// system(mypid);
}

void	setup_pipe_cmd(t_list *list, t_newcommand *cmd)
{
	t_newcommand *temp = cmd;

	setup_pipes(cmd);
	while (temp)
	{
		
		run_pipes(list, temp);
		temp = temp->next;
	}
	waitpid(g_global.pid, 0, 0);
	// clean_tokens_child(list, cmd);
	clean_pipes(cmd);
	// wait(NULL);
}
