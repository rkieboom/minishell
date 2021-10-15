/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/15 14:13:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	create_line(t_list *list, int k)
{
	int i;

	i = 0;
	list->cmd[k].cmd = ft_calloc(list->tokens[k].token_pos[0] + 1, sizeof(char*));// moet een *** 
	while (i < list->tokens[k].token_pos[0])
	{
		list->cmd[k].cmd[i] = list->parse.commands[k][i];
		i++;
	}
	list->tokens[k].fd = open(list->parse.commands[k][i + 1], O_CREAT, O_RDWR);
	if (list->tokens[k].fd < 0)
		return ;
	dup2(1, list->tokens[k].fd);
}

static void	create_cmd(t_list *list)
{
	int k;

	k = 0;
	while (list->parse.commands[k])
		k++;
	list->cmd = ft_calloc(k + 1, sizeof(t_cmd));
	k = 0;
	while (list->parse.commands[k])
	{
		if (list->tokens[k].total > 0)
			create_line(list, k);
		else
			list->cmd[k].cmd = list->parse.commands[k];
			
		k++;
	}
}

void		execute(t_list *list)
{
	create_cmd(list);
	checkcommand(list);
	dup2(list->stdout_cpy, 1);
}
