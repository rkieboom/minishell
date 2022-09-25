/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 01:37:44 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/22 14:09:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes/pipes.h"

static void	go(t_list *list, t_newcommand *cmd, char **newcmd)
{
	t_heredoc_data	*data;

	data = cmd->tokens->heredoc->data;
	while (data)
	{
		set_pipe_heredoc(cmd->tokens->heredoc, data);
		if (!redirections(list, cmd))
		{
			run_cmd(list, newcmd);
			if (write(1, "\n", 1) < 0)
				ft_ret_exit(1, 1);
		}
		reset_redirections(list, cmd);
		clear_pipe_heredoc(cmd->tokens->heredoc);
		data = data->next;
	}
}

void	run_cmd_heredoc(t_list *list, t_newcommand *cmd)
{
	char	**newcmd;

	newcmd = set_cmd(cmd);
	if (!newcmd)
		ft_ret_exit(1, 0);
	if (!newcmd[0])
	{
		free(newcmd);
		return ;
	}
	go(list, cmd, newcmd);
	free(newcmd);
}
