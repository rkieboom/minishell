/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:39:19 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/09 00:19:33 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	init_vars(t_tokens *tokens)
{
	tokens->last_l = -1;
	tokens->last_r = -1;
}

static int	loop_over(t_newcommand *v, int i, int total)
{
	while (i < total)
	{
		if (!ft_strncmp(v->tokens->token[i], "<<", 3))
			double_redirection_left(v, i);
		else if (!ft_strncmp(v->tokens->token[i], "<", 2))
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

void	reset_redirections(t_list *list, t_newcommand *v)
{
	if (v->tokens->single_redirection_left > 0)
	{
		close(v->tokens->stdin_fd);
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
	init_vars(v->tokens);
	if (loop_over(v, 0, v->tokens->total))
		return (1);
	if (set_redir(list, v))
		return (1);
	return (0);
}
