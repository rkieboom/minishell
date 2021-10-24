/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_parse_commands.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/24 19:14:12 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_parse_commands(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (list->parse.commands)
	{
		while (list->parse.commands[i])
		{
			while (list->parse.commands[i][j])
			{
				free(list->parse.commands[i][j]);
				j++;
			}
			j = 0;
			free(list->parse.commands[i]);
			i++;
		}
		free(list->parse.commands);
	}
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = NULL;
	}
	i = 0;
	while (list->cmd.size >= 0)
	{
		if (list->cmd.free[list->cmd.size] == 1)
			free(list->cmd.cmd[list->cmd.size]);
		list->cmd.size--;
	}
	free(list->cmd.cmd);
	free(list->cmd.free);
	free(list->tokens);
}
