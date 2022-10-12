/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 20:16:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


// static void	save_fds(t_list *list)
// {
// 	list->stdin_cpy = dup(0);
// 	list->stdout_cpy = dup(1);
// }

// static void	reset_fds(t_list *list)
// {
// 	dup2(list->stdin_cpy, 0);
// 	close(list->stdin_cpy);
// 	dup2(list->stdout_cpy, 1);
// 	close(list->stdout_cpy);
// }

void	execution(t_list *list, t_newcommand *cmd, int k)
{
	int	i;

	i = 0;
	while (list->parse.commands[k])
		k++;
	while (i < k)
	{
		if (!cmd[i].next)
			setup_single_cmd(list, cmd);
		else
			setup_pipe_cmd(list, cmd);
		i++;
	}
	dprintf(2, "DONE WITH ALL\n");
}
