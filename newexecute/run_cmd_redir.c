/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 15:57:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/27 19:23:45 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_token(t_newcommand *cmd)

static char	**init_newcmd_s(char **cmd, int k)
{
	int	i;
	char	**newcmd;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "<<", 3) \
		!ft_strncmp(cmd[i], ">>", 3) \
		!ft_strncmp(cmd[i], ">", 2) \
		!ft_strncmp(cmd[i], "<", 2))
		{//nog verder kijken of het een token is
			i++;
			if (!cmd[i])
			{
				newcmd = ft_calloc(1, sizeof(char *));
				if (!newcmd)
					ft_ret_exit(1, 1);
				newcmd[0] = 0;
				return (newcmd);
			}
			i++;
		}
		else
		{
			while () //terwijl cmd[i] niet gelijk is aan een token.
		}
	}
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
		return (init_newcmd_s(cmd->command, i));
	return (init_newcmd(cmd->command, i));
}

void	run_cmd_redir(t_list *list, t_newcommand *v)
{
	char	**newcmd;

	newcmd = set_cmd(v);
	if (!newcmd[0])
	{
		free(newcmd);
		return ;
	}
	run_cmd(list, newcmd);
	if (v->tokens && v->tokens->total > 0)
		free(newcmd);
}
