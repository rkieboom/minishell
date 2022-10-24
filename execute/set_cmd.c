/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 15:57:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 13:23:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		length;
	char	**newcmd;
}				t_vars;

int	is_token(t_newcommand *cmd, int k)
{
	int	i;

	i = 0;
	while (i < cmd->tokens->total)
	{
		if (cmd->tokens->token_pos[i] == k)
			return (1);
		i++;
	}
	return (0);
}

static void	count_len(t_vars *vars, t_newcommand *cmd)
{
	while (cmd->command[vars->i + vars->length])
	{
		if (is_token(cmd, vars->i))
		{
			vars->i++;
			if (!cmd->command[vars->i])
				return ;
			vars->i++;
		}
		else
		{
			while (cmd->command[vars->i + vars->length] \
			&& is_token(cmd, vars->i + vars->length) == 0)
				vars->length++;
			return ;
		}
	}
}	

static char	**init_newcmd_s(t_newcommand *cmd)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	count_len(&vars, cmd);
	if (!cmd->command[vars.i] || vars.length == 0)
	{
		vars.newcmd = ft_calloc(1, sizeof(char *));
		if (!vars.newcmd)
			ft_ret_exit(1, 1);
		vars.newcmd[0] = 0;
		return (vars.newcmd);
	}
	vars.newcmd = ft_calloc(vars.length + 1, sizeof(char *));
	if (!vars.newcmd)
		ft_ret_exit(1, 1);
	while (vars.j < vars.length)
	{
		vars.newcmd[vars.j] = cmd->command[vars.i + vars.j];
		vars.j++;
	}
	vars.newcmd[vars.length] = 0;
	return (vars.newcmd);
}

static char	**init_newcmd(char **cmd, int k)
{
	char	**newcmd;
	int		i;

	i = 0;
	newcmd = ft_calloc(k + 1, sizeof(char *));
	if (!newcmd)
		ft_ret_exit(1, 1);
	while (i < k)
	{
		newcmd[i] = cmd[i];
		i++;
	}
	newcmd[i] = 0;
	return (newcmd);
}

char	**set_cmd(t_newcommand *cmd)
{
	int	i;

	i = 0;
	if (!cmd->tokens || cmd->tokens->total == 0)
		return (cmd->command);
	while (cmd->tokens->total < i)
	{
		if (cmd->tokens->token_pos[i] && \
		(ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], "<", 2) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], ">", 2) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], "<<", 3) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], ">>", 3)))
			break ;
		i++;
	}
	i = cmd->tokens->token_pos[i];
	if (i == 0)
		return (init_newcmd_s(cmd));
	return (init_newcmd(cmd->command, i));
}

static int	calc_len(t_newcommand *cmd)
{
	int	i;

	i = 0;
	while (cmd->command[i])
		i++;
	return (i - (cmd->tokens->total * 2));
}

static char*	get_str(t_newcommand *cmd, int i)
{
	int	token_c = 0;
	int	c = 0;
	int	s = 0;

	while (cmd->command[c + s])
	{
		if (token_c < cmd->tokens->total && \
		((c + s) == cmd->tokens->token_pos[token_c]))
		{
			s += 2;
			token_c++;
		}
		if (c == i)
			return (cmd->command[c + s]);
		c++;
	}
	return (0);
}
//echo hou oke >> naam1 doei >> naam2 doei

char	**set_newcmd(t_newcommand *cmd)
{
	int		i;
	int		length;
	char	**newstr;

	i = 0;
	if (!cmd->tokens || cmd->tokens->total == 0)
		return (cmd->command);
	length = calc_len(cmd);
	newstr = ft_calloc(length + 1, sizeof(char *));
	while (i < length)
	{
		newstr[i] = get_str(cmd, i);
		i++;
	}
	newstr[length] = 0;
	return (newstr);
}
