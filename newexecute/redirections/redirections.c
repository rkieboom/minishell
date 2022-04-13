/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:39:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/13 17:07:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	loop_over(t_newcommand *v, int i, int total)
{
	while (i < total)
	{
		if (!ft_strncmp(v->tokens->token[i], "<", 2))
		{
			if (single_redirection_left(v, i) < 0)
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">>", 3))
			double_redirection_right(v, i);
		else if (!ft_strncmp(v->tokens->token[i], ">", 2))
			single_redirection_right(v, i);
		i++;
	}
	return (0);
}

static int	set_redir(t_list *list, t_newcommand *v)
{
	if (v->tokens->last_l > 0)
	{
		v->tokens->stdin_fd = open(v->command[v->tokens->last_l + 1], O_RDONLY);
		if (v->tokens->stdin_fd < 0)
		{
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putstr_fd(v->command[v->tokens->last_l + 1], 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
		list->stdin_cpy = dup(0);
		if (list->stdin_cpy < 0)
			ft_exit(1, 1);
		close(0);
		if (dup2(v->tokens->stdin_fd, 0) < 0)
			ft_exit(1, 1);
	}
	if (v->tokens->last_r > 0)
	{
		list->stdout_cpy = dup(1);
		close(1);
		if (!strncmp(v->command[v->tokens->last_r], ">>", 3))
			v->tokens->stdout_fd = open(v->command[v->tokens->last_r + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			v->tokens->stdout_fd = open(v->command[v->tokens->last_r + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (v->tokens->stdout_fd < 0)
			ft_exit(1, 1);
		if (dup2(v->tokens->stdout_fd, 1) < 0)
			ft_exit(1, 1);
	}
	return (0);
}

void	reset_redirections(t_list *list, t_newcommand *v)
{
	if (v->tokens->single_redirection_left > 0)
	{
		close(v->tokens->stdin_fd);
		if (dup2(list->stdin_cpy, 0) < 0)
			ft_exit(1, 1);
	}
	if (v->tokens->single_redirection_right > 0 \
	|| v->tokens->double_redirection_right > 0)
	{
		close(v->tokens->stdout_fd);
		if (dup2(list->stdout_cpy, 1) < 0)
			ft_exit(1, 1);
	}
}

int	redirections(t_list *list, t_newcommand *v)
{
	int	i;

	i = 0;
	if (loop_over(v, 0, v->tokens->total))
		return (1);
	if (set_redir(list, v) < 0)
		return (1);
	return (0);
}
