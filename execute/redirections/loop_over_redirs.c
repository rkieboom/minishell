/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_over_redirs.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:58:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 14:13:11 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	single_redirection_right(t_newcommand *v, int i)
{
	v->tokens->stdout_fd = open(\
	v->command[v->tokens->token_pos[i] + 1] \
	, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
	{
		ft_ret_exit(0, 1);
		return (1);
	}
	close(v->tokens->stdout_fd);
	v->tokens->last_r = v->tokens->token_pos[i];
	return (0);
}

static int	double_redirection_right(t_newcommand *v, int i)
{
	v->tokens->stdout_fd = open(\
	v->command[v->tokens->token_pos[i] + 1] \
	, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
	{
		ft_ret_exit(0, 1);
		return (1);
	}
	close(v->tokens->stdout_fd);
	v->tokens->last_r = v->tokens->token_pos[i];
	return (0);
}

static int	single_redirection_left(t_newcommand *v, int i)
{
	v->tokens->stdin_fd = open(\
	v->command[v->tokens->token_pos[i] + 1], O_RDONLY);
	if (v->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("minishell-4.2$: no such file or directory: ", 2);
		ft_putstr_fd(v->command[v->tokens->token_pos[i] + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	close(v->tokens->stdin_fd);
	v->tokens->last_l = v->tokens->token_pos[i];
	return (0);
}

static void	double_redirection_left(t_newcommand *v, int i)
{
	v->tokens->last_l = v->tokens->token_pos[i];
}

int	loop_over_redirs(t_newcommand *v, int i, int total)
{
	v->tokens->last_l = -1;
	v->tokens->last_r = -1;
	while (i < total)
	{
		if (!ft_strncmp(v->tokens->token[i], "<<", 3))
			double_redirection_left(v, i);
		else if (!ft_strncmp(v->tokens->token[i], "<", 2))
		{
			if (single_redirection_left(v, i))
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">>", 3))
		{
			if (double_redirection_right(v, i))
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">", 2))
		{
			if (single_redirection_right(v, i))
				return (1);
		}
		i++;
	}
	return (0);
}
