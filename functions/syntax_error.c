/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:11:34 by rkieboom      ########   odam.nl         */
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

//Checks for double tokens
static int	check_double_pipe_error(t_vars *vars, t_list *list)
{
	if (list->tokens[vars->i].token_pos[vars->j] + 1 == \
	list->tokens[vars->i].token_pos[vars->j + 1] && \
	!ft_strncmp(list->tokens[vars->i].token[vars->j], "|", 2) && \
	!ft_strncmp(list->tokens[vars->i].token[vars->j + 1], "|", 2))
	{
		ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `|'\n", 2);
		g_global.status = 258;
		return (1);
	}
	return (0);
}

//Checks if 2 tokens are next to each other
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
			g_global.status = 258;
			return (1);
		}
		else if (check_double_pipe_error(vars, list))
			return (1);
		vars->j++;
	}
	return (0);
}

//Checks if CMD arg0 = '|'
static int	first(t_vars *vars, t_list *list)
{
	vars->j = 0;
	while (vars->i < vars->k && (&list->tokens[vars->i] == NULL \
	|| list->tokens[vars->i].total == 0))
		vars->i++;
	if (vars->i == vars->k)
		return (1);
	if (!ft_strncmp(list->tokens[vars->i].token[0], "|", 2) \
	&& list->tokens[vars->i].token_pos[vars->j] == 0)
	{
		ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `|'", 2);
		g_global.status = 258;
		return (2);
	}
	return (3);
}

//Check for syntax errors otherwise quit
int	syntax_error_parse(t_list *list)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (list->parse.commands[vars.k])
		vars.k++;
	while (vars.i < vars.k)
	{
		vars.temp = first(&vars, list);
		if (vars.temp == 1)
			return (0);
		else if (vars.temp == 2)
			return (1);
		if (loop_over_tokens(&vars, list))
			return (1);
		vars.i++;
	}
	return (0);
}

//Checks syntax errors for tokens
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
				ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `newline'", 2);
				g_global.status = 258;
				return (1);
			}
		}
		else if (cmd->tokens->token_pos[i] + 1 == cmd->tokens->token_pos[i + 1])
		{
			ft_putstr_fd("minishell-4.2$: syntax error near token ", 2);
			ft_putendl_fd(cmd->tokens->token[i + 1], 2);
			g_global.status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
