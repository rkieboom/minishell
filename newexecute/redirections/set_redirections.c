/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_redirections.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 13:35:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/08 17:23:46 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	redir_left(t_list *list, t_newcommand *v)
{
	v->tokens->stdin_fd = open(v->command[v->tokens->last_l + 1], O_RDONLY);
	if (v->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(v->command[v->tokens->last_l + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	list->stdin_cpy = dup(0);
	if (list->stdin_cpy < 0)
		ft_ret_exit(1, 1);
	close(0);
	if (dup2(v->tokens->stdin_fd, 0) < 0)
		ft_ret_exit(1, 1);
	return (0);
}

static void	redir_right(t_list *list, t_newcommand *v)
{
	list->stdout_cpy = dup(1);
	close(1);
	if (!strncmp(v->command[v->tokens->last_r], ">>", 3))
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
		ft_ret_exit(1, 1);
	if (dup2(v->tokens->stdout_fd, 1) < 0)
		ft_ret_exit(1, 1);
}

int	set_redir(t_list *list, t_newcommand *v)
{
	if (v->tokens->last_l >= 0)
	{
		if (redir_left(list, v))
			return (1);
	}
	// if (v->tokens->double_redirection_left)
	// {
		
	// }
	if (v->tokens->last_r >= 0)
		redir_right(list, v);
	return (0);
}
