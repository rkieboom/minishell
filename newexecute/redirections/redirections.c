/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:39:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/21 17:06:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	reset_redirections(t_list *list, t_newcommand *v)
{
	if (v->tokens->single_redirection_left > 0 && \
	!ft_strncmp(v->command[v->tokens->last_l], "<", 2))
	{
		close(v->tokens->stdin_fd);
		if (dup2(list->stdin_cpy, 0) < 0)
			ft_ret_exit(1, 1);
	}
	else if (v->tokens->double_redirection_left > 0)
	{
		close(v->tokens->heredoc->pipe[0]);
		if (dup2(list->stdin_cpy, 0) < 0)
			ft_ret_exit(1, 1);
	}
	if (v->tokens->single_redirection_right > 0 \
	|| v->tokens->double_redirection_right > 0)
	{
		close(v->tokens->stdout_fd);
		if (dup2(list->stdout_cpy, 1) < 0)
			ft_ret_exit(1, 1);
	}
}

int	redirections(t_list *list, t_newcommand *v)
{
	if (set_redir(list, v))
		return (1);
	return (0);
}
