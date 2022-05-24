/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/18 13:15:46 by rkieboom      ########   odam.nl         */
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

int	syntax_error(t_newcommand *cmd)
{
	int	i;

	i = 0;
	if (!cmd->tokens || cmd->tokens->total == 0)
		return (0);
	while (i < cmd->tokens->total)
	{
		if (i + 1 == cmd->tokens->total)//laatste
		{
			if (cmd->tokens->token_pos[i] == cmd_len(cmd->command) - 1) //cat main.c >            laatste arg is een token
			{
				ft_putendl_fd("minishell-4.2$: syntax error near newline", 2);
				return (1);
			}
			return (0);
		}
		else if (cmd->tokens->token_pos[i] + 1 == cmd->tokens->token_pos[i + 1])//als 2 tokens naast elkaar zitten
		{
			ft_putstr_fd("minishell-4.2$: syntax error near token ", 2);
			ft_putendl_fd(cmd->tokens->token[i + 1], 2);//token zelf 
			return (1);
		}
		i++;
	}
	return (0);
}
