/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_functions.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:45:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/04 12:03:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	single_redirection_right(t_newcommand *v, int i)
{
	v->tokens->stdout_fd = open(v->command[v->tokens->token_pos[i] + 1],  O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
		ft_ret_exit(1, 1);
	close(v->tokens->stdout_fd);
	v->tokens->last_r = v->tokens->token_pos[i];
}

void	double_redirection_right(t_newcommand *v, int i)
{
	v->tokens->stdout_fd = open(v->command[v->tokens->token_pos[i] + 1],  O_RDWR | O_APPEND | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
		ft_ret_exit(1, 1);
	close(v->tokens->stdout_fd);
	v->tokens->last_r = v->tokens->token_pos[i];
}

int	single_redirection_left(t_newcommand *v, int i)
{
	v->tokens->stdin_fd = open(v->command[v->tokens->token_pos[i] + 1], O_RDONLY);
	if (v->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(v->command[v->tokens->token_pos[i] + 1], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	close(v->tokens->stdin_fd);
	v->tokens->last_l = v->tokens->token_pos[i];
	return (0);
}
