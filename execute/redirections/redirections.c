/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 22:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 10:19:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	tokens_exist(t_newcommand *cmd)
{
	if (cmd->tokens && cmd->tokens->total > 0)
		return (1);
	else
		return (0);
}

int	redir_left(t_newcommand *v)
{
	if (!ft_strncmp(v->command[v->tokens->last_l], "<<", 3))
	{
		heredoc_set_pipe(&v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1], \
v->tokens->heredoc[v->tokens->double_redirection_left - 1].data);
		if (dup2(v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1].pipe[0], 0) < 0)
			ft_ret_exit(1, 1);
		close(v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1].pipe[0]);
		return (0);
	}
	v->tokens->stdin_fd = open(v->command[v->tokens->last_l + 1], O_RDONLY);
	if (v->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("minishell-4.2$: no such file or directory: ", 2);
		ft_putstr_fd(v->command[v->tokens->last_l + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	if (dup2(v->tokens->stdin_fd, 0) < 0)
		ft_ret_exit(1, 1);
	close(v->tokens->stdin_fd);
	return (0);
}

int	redir_right(t_newcommand *v)
{
	if (!strncmp(v->command[v->tokens->last_r], ">>", 3))
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
	{
		ft_ret_exit(0, 1);
		return (1);
	}
	if (dup2(v->tokens->stdout_fd, 1) < 0)
		ft_ret_exit(1, 1);
	close(v->tokens->stdout_fd);
	return (0);
}

int	redirections(t_newcommand *cmd)
{
	if (tokens_exist(cmd) && loop_over_redirs(cmd, 0, cmd->tokens->total))
		return (1);
	if (tokens_exist(cmd) && cmd->tokens->last_l != -1)
	{
		if (redir_left(cmd))
			return (1);
	}
	if (tokens_exist(cmd) && cmd->tokens->last_r != -1)
	{
		if (redir_right(cmd))
			return (1);
	}
	return (0);
}
