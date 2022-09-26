/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/26 15:04:20 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

typedef struct s_vars
{
	int	i;
	int	j;
	int	k;
	int	temp;
}				t_vars;

int	cmd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	loop_over_tokens(t_vars *vars, t_list *list)
{
	while (vars->j < list->tokens[vars->i].total)
	{
		if (list->tokens[vars->i].token_pos[vars->j] + 1 == \
		list->tokens[vars->i].token_pos[vars->j + 1] && \
		ft_strncmp(list->tokens[vars->i].token[vars->j], "|", 2))
		{
			ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `", 2);
			ft_putstr_fd(list->tokens[vars->i].token[vars->j + 1], 2);
			ft_putendl_fd("'", 2);
			g_ret = 258;
			return (1);
		}
		j++;
	}
	return (0);
}

static int	first(t_vars *vars, t_list *list)
{
	j = 0;
	while (i < k && (&list->tokens[i] == NULL \
	|| list->tokens[i].total == 0))
		i++;
	if (i == k)
		return (1);
	if (!ft_strncmp(list->tokens[i].token[0], "|", 2) \
	&& list->tokens[i].token_pos[j] == 0)
	{
		ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `|'", 2);
		g_ret = 258;
		return (2);
	}
	return (3);
}

int	syntax_error_parse(t_list *list)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (list->parse.commands[k])
		k++;
	while (i < k)
	{
		temp = first(&vars, list);
		if (temp == 1)
			return (0);
		else if (temp == 2)
			return (1);
		if (loop_over_tokens(&vars, list))
			return (1);
		if (!list->parse.commands[i][list->tokens[i].token_pos[j] + 1])
		{
			ft_putendl_fd(\
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
