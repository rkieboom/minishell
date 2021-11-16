/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/16 20:20:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/16 20:21:11 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	single_redirection_left(t_list *list, int k, int i)
{
	if (i == 0)
	{
		list->stdin_cpy = dup(0);
		close(0);
		list->tokens[k].stdin_fd = open(list->parse.commands[k] \
			[list->tokens[k].token_pos[i] + 1], O_RDONLY);
		dup2(list->tokens[k].stdin_fd, 0);
	}
	else
	{
		list->tokens[k].stdin_fd = open(list->parse.commands[k] \
				[list->tokens[k].token_pos[i] + 1], O_RDONLY);
		if (list->tokens[k].stdin_fd < 0)
			ft_exit(1, 1);
	}
}

static void	single_redirection_right(t_list *list, int k, int i)
{
	list->tokens[k].stdout_fd = open(list->parse.commands[k] \
	[list->tokens[k].token_pos[i] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(list->tokens[k].stdout_fd);
}

static void	double_redirection_right(t_list *list, int k, int i)
{
	list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	close(list->tokens[k].stdout_fd);
}

void	set_redirection(t_list *list, int k)
{
	int	i;
	int	total;

	i = 0;
	total = list->tokens[k].total;
	if (total <= 0)
		return ;
	while (total)
	{
		if (!ft_strncmp(list->tokens[k].token[i], "<", 2))
			single_redirection_left(list, k, i);
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
			double_redirection_right(list, k, i);
		else if (!ft_strncmp(list->tokens[k].token[i], ">", 2))
			single_redirection_right(list, k, i);
		i++;
		total--;
	}
}
