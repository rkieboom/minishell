/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_parse_commands.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/30 02:03:24 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_parse_commands(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	while (list->cmd.size > 0)
	{
		if (list->cmd.free[list->cmd.size - 1] == 1)
			free(list->cmd.cmd[list->cmd.size - 1]);
		list->cmd.size--;
	}
	while (list->parse.commands[i])
	{
		while(list->tokens[i].total)
		{
			free(list->tokens[i].token[list->tokens[i].total - 1]);
			list->tokens[i].total--;
		}
		free(list->tokens[i].token);
		free(list->tokens[i].token_pos);
		i++;
	}
	i = 0;
	if (list->parse.commands)
	{
		while (list->parse.commands[i])
		{
			j = 0;
			while (list->parse.commands[i][j])
			{
				free(list->parse.commands[i][j]);
				j++;
			}
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
	free(list->cmd.cmd);
	free(list->cmd.free);
	free(list->tokens);
}
