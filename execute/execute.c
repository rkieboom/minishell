/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/08 18:39:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	create_line(t_list *list, int k)
{
	int	i;
	int j;

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

static void	set_redirection(t_list *list, int k)
{
	int	i;
	int	total;

	i = 0;
	total = list->tokens[k].total;
	if (total <= 0)
		return ;
	while (total)
	{
		if (i == 0 && (!ft_strncmp(list->tokens[k].token[i], "<", 2)))
		{
			list->stdin_cpy = dup(0);
			close(0);
			list->tokens[k].stdin_fd = open(list->parse.commands[k] \
				[list->tokens[k].token_pos[i] + 1], O_RDONLY);
			dup2(list->tokens[k].stdin_fd, 0);
		}
		else if (total - 1 == 0)
		{
			list->stdout_cpy = dup(1);
			close(1);
			if (!ft_strncmp(list->tokens[k].token[i], ">>", 3))
				list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
			else if (!ft_strncmp(list->tokens[k].token[i], ">", 2))
				list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			dup2(list->tokens[k].stdout_fd, 1);
		}
		else if (!ft_strncmp(list->tokens[k].token[i], ">>", 3))
		{
			list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
			close(list->tokens[k].stdout_fd);
		}
		else if (!ft_strncmp(list->tokens[k].token[i], ">", 2))
		{
			list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			close(list->tokens[k].stdout_fd);
		}
		i++;
		total--;
	}
}

void		execute(t_list *list)
{
	int	i;
	int	k;
	
	i = 0;
	k = create_cmd(list);
	while (list->parse.commands[i])
	{
		if (list->tokens[i].total > 0)
			set_redirection(list, i);
		checkcommand(list, i);
		if (list->tokens[i].total > 0)
		{
			if (list->tokens[i].single_redirection_left == 1)
			{
				close(list->tokens[i].stdin_fd);
				dup2(list->stdin_cpy, 0);
			}
			if (list->tokens[i].single_redirection_right == 1 || list->tokens[i].double_redirection_right == 1)
			{
				close(list->tokens[i].stdout_fd);
				dup2(list->stdout_cpy, 1);
			}
		}
		i++;
	}
}

// void		execute(t_list *list)
// {
// 	int	i;
// 	int	k;
	
// 	i = 0;
// 	k = create_cmd(list);
// 	while (list->parse.commands[i])
// 	{
// 		list->stdout_cpy = dup(1);
// 		set_redirection(list, i);
// 		checkcommand(list, i);
// 		write(1, "kanker\n", 6);
// 		if (list->tokens[i].total > 0)
// 			close(list->tokens[i].fd);
// 		dup2(list->stdout_cpy, 1);
// 		i++;
// 	}
// }