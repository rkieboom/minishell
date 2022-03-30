/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/17 12:38:18 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	create_line(t_list *list, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	list->cmd.cmd[k] = ft_calloc \
	(list->tokens[k].token_pos[0] + 1, sizeof(char *));
	list->cmd.free[k] = 1;
	while (i < list->tokens[k].token_pos[0])
	{
		list->cmd.cmd[k][i] = list->parse.commands[k][i + j];
		i++;
	}
}

static int	create_cmd(t_list *list)
{
	int	k;

	k = 0;
	while (list->parse.commands[k])
		k++;
	list->cmd.size = k;
	list->cmd.cmd = ft_calloc(k, sizeof(t_cmd));
	list->cmd.free = ft_calloc(k, sizeof(int));
	k = 0;
	while (list->parse.commands[k])
	{
		if (list->tokens[k].total > 0)
			create_line(list, k);
		else
			list->cmd.cmd[k] = list->parse.commands[k];
		k++;
	}
	return (k);
}

void	execute(t_list *list)
{
	int	i;
	int	k;

	i = 0;
	k = create_cmd(list);
	while (list->parse.commands[i])
	{
		if (list->tokens[i].pipe >= 1)
			createcommand_pipe(list, i); //
		else if (list->tokens[i].total > 0)
		{
			if (set_redirection(list, i) == 0)
			{
				checkcommand(list, i);
				if (list->tokens[i].single_redirection_left == 1)
				{
					close(list->tokens[i].stdin_fd);
					dup2(list->stdin_cpy, 0);
				}
				if (list->tokens[i].single_redirection_right == 1 \
				|| list->tokens[i].double_redirection_right == 1)
				{
					close(list->tokens[i].stdout_fd);
					dup2(list->stdout_cpy, 1);
				}
			}
		}
		else
			checkcommand(list, i);
		i++;
	}
}
