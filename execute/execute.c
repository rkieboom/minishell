/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/22 16:56:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execution(t_list *list, t_newcommand *cmd, int k)
{
	int	i;

	i = 0;
	while (list->parse.commands[k])
		k++;
	tcsetattr(0, 0, &g_global.termios_save);
	signals();
	while (i < k)
	{
		if (!cmd[i].next)
			setup_single_cmd(list, &cmd[i]);
		else
			setup_pipe_cmd(list, &cmd[i]);
		i++;
	}
}
