/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/16 20:20:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/24 16:17:50 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	single_redirection_left(t_list *list, int k, int i)
{
	list->tokens[k].stdin_fd = open(list->parse.commands[k] \
		[list->tokens[k].token_pos[i] + 1], O_RDONLY);
	if (list->tokens[k].stdin_fd < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(list->parse.commands[k] \
			[list->tokens[k].token_pos[i] + 1], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (0);
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

int	set_redirection(t_list *list, int k)
{
	int	i;
	int	total;

	i = 0;
	total = list->tokens[k].total;
	if (total <= 0)
		return (0);
	while (total)
	{
		if (!ft_strncmp(list->tokens[k].token[i], "<", 2))
		{
			if (single_redirection_left(list, k, i) < 0)
				return (1);
		}
		else if (!ft_strncmp(list->tokens[k].token[i], ">>", 3))
			double_redirection_right(list, k, i);
		else if (!ft_strncmp(list->tokens[k].token[i], ">", 2))
			single_redirection_right(list, k, i);
		i++;
		total--;
	}
	return (0);
}
	// if () // MOET LAATSTE ZIJN < | <<
	// {
	// 	list->tokens[k].stdin_fd = open(list->parse.commands[k] \
	// 		[list->tokens[k].token_pos[i] + 1], O_RDONLY);
	// 	if (list->tokens[k].stdin_fd < 0)
	// 	{
	// 		ft_putstr_fd("no such file or directory: ", 2);
	// 		ft_putstr_fd(list->parse.commands[k] \
	// 			[list->tokens[k].token_pos[i] + 1], 2);
	// 		ft_putchar_fd('\n', 2);
	// 		return ;
	// 	}	
	// 	list->stdin_cpy = dup(0);
	// 	close(0);
	// 	dup2(list->tokens[k].stdin_fd, 0);
	// }



		// else if (total - 1 == 0) //de LAATSTE > | >>
		// {
		// 	list->stdout_cpy = dup(1);
		// 	close(1);
		// 	if (!ft_strncmp(list->tokens[k].token[i], ">>", 3))
		// 		list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		// [list->tokens[k].token_pos[i] + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
		// 	else if (!ft_strncmp(list->tokens[k].token[i], ">", 2))
		// 		list->tokens[k].stdout_fd = open(list->parse.commands[k] \
		// [list->tokens[k].token_pos[i] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		// 	dup2(list->tokens[k].stdout_fd, 1);
		// }