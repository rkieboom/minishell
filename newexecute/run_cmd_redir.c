/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 15:57:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/11 17:32:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char **init_newcmd(char **cmd, int k)
{
	char **newcmd;
	int	i;
	
	i = 0;
	newcmd = ft_calloc(i, sizeof(char *));
	if (!newcmd)
		ft_ret_exit(1, 1);
	while (i < k)
	{
		newcmd[i] = cmd[i];//heap overflow on linux????????
		i++;
	}
	newcmd[i] = 0;
	return (newcmd);
}

char **set_cmd(t_newcommand *cmd)
{
	int	i;

	i = 0;
	while (cmd->tokens->total < i)
	{
		if (cmd->tokens->token_pos[i] && (ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], "<", 2) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], ">", 2) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], "<<", 3) \
		|| ft_strncmp(cmd->tokens->token[cmd->tokens->token_pos[i]], ">>", 3))) \
			break ;
		i++;
	}
	i = cmd->tokens->token_pos[i];
	return (init_newcmd(cmd->command, i));
}

void	run_cmd_redir(t_list *list, t_newcommand *v)
{
	char	**newcmd;

	newcmd = set_cmd(v);
	if (!newcmd)
	ft_ret_exit(0, 1);
	if (!ft_strncmp(newcmd[0], "echo", 5))
		list->ret = echo(newcmd);
	else if (!ft_strncmp(newcmd[0], "cd", 3))
		list->ret = cd(list, newcmd);
	else if (!ft_strncmp(newcmd[0], "pwd", 4))
		list->ret = pwd();
	else if (!ft_strncmp(newcmd[0], "export", 7))
		list->ret = export(list->env, newcmd);
	else if (!ft_strncmp(newcmd[0], "unset", 6))
		list->ret = unset(list->env, newcmd);
	else if (!ft_strncmp(newcmd[0], "env", 4))
		list->ret = env(list->env);
	else if (!ft_strncmp(newcmd[0], "exit", 5))
		ft_exit(newcmd);
	else
		list->ret = ft_execve(list, newcmd);
	free(newcmd);
}
