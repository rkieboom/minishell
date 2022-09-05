/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/05 14:11:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	cmd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	syntax_error(t_newcommand *cmd, int i)
{
	if (!cmd->tokens || cmd->tokens->total == 0)
		return (0);
	while (i < cmd->tokens->total)
	{
		if (i + 1 == cmd->tokens->total)
		{
			if (cmd->tokens->token_pos[i] == cmd_len(cmd->command) - 1)
			{
				ft_putendl_fd("minishell-4.2$: syntax error near newline", 2);
				g_ret = 258;
				return (1);
			}
		}
		else if (cmd->tokens->token_pos[i] + 1 == cmd->tokens->token_pos[i + 1])
		{
			ft_putstr_fd("minishell-4.2$: syntax error near token ", 2);
			ft_putendl_fd(cmd->tokens->token[i + 1], 2);
			g_ret = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
