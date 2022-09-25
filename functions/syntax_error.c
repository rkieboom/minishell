/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/23 17:29:58 by rkieboom      ########   odam.nl         */
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

int	syntax_error_parse(t_list *list)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (list->parse.commands[k])
		k++;
	while (i < k)
	{
		j = 0;
		while (i < k && (&list->tokens[i] == NULL || list->tokens[i].total == 0))
			i++;
		if (i == k)
			return (0);
		if (!ft_strncmp(list->tokens[i].token[0], "|", 2) \
		&& list->tokens[i].token_pos[j] == 0)
		{
			ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `|'\n", 2);
			g_ret = 258;
			return (1);
		}
		while (j < list->tokens[i].total)
		{
			if (list->tokens[i].token_pos[j] + 1 == \
			list->tokens[i].token_pos[j + 1] && \
			ft_strncmp(list->tokens[i].token[j], "|", 2))
			{
				ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `", 2);
				ft_putstr_fd(list->tokens[i].token[j + 1], 2);
				ft_putendl_fd("'\n", 2);
				g_ret = 258;
				return (1);
			}
			j++;
		}
		if (!list->parse.commands[i][list->tokens[i].token_pos[j] + 1])
		{
			ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `newline'", 2);
			g_ret = 258;
			return (1);
		}
		i++;
	}
	return (0);
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
