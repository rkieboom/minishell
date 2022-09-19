/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 20:38:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/19 20:44:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	return (init_newcmd(cmd->command, i));
}

static int	run_cmd()
{
	if (!ft_strncmp(newcmd[0], "echo", 5))
		g_ret = echo(newcmd);
	else if (!ft_strncmp(newcmd[0], "cd", 3))
		g_ret = cd(list, newcmd);
	else if (!ft_strncmp(newcmd[0], "pwd", 4))
		g_ret = pwd();
	else if (!ft_strncmp(newcmd[0], "export", 7))
		g_ret = export(list->env, newcmd);
	else if (!ft_strncmp(newcmd[0], "unset", 6))
		g_ret = unset(list->env, newcmd);
	else if (!ft_strncmp(newcmd[0], "env", 4))
		g_ret = env(list->env);
	else if (!ft_strncmp(newcmd[0], "exit", 5))
		ft_exit(newcmd);
	else
		g_ret = ft_execve(list, newcmd, 0);
}

int	run_cmd_heredoc(t_newcommand *cmd)
{
	char **newcmd;
	t_heredoc_data *temp;

	newcmd = set_cmd(cmd);
	while (temp)
	{
		temp->

		temp = temp->next;
	}
}
