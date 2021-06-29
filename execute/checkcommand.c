/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/06/29 16:04:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	printerror(const char *str)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd((char*)str, 2);
}

void		checkcommand(t_list *list)
{
	int	i;
	int j;
	
	i = 0;
	while (list->parse.commands[i])
	{
		if (!ft_strncmp(list->parse.commands[i][0], "echo", 5))
			ft_echo(list, list->parse.commands[i]);
		else if (!ft_strncmp(list->parse.commands[i][0], "cd", 3))
			cd(list, list->parse.commands[i]);
		else if (!ft_strncmp(list->parse.commands[i][0], "pwd", 4))
			pwd(list->env);
		else if (!ft_strncmp(list->parse.commands[i][0], "export", 7))
			break ;
		else if (!ft_strncmp(list->parse.commands[i][0], "unset", 6))
			break ;
		else if (!ft_strncmp(list->parse.commands[i][0], "env", 4))
			env(list->env);
		else if (!ft_strncmp(list->parse.commands[i][0], "exit", 5))
			exit(0);
		else
			ft_putendl_fd("werkt nog niet kut!", 1);
			// ft_execve(list, list->parse.commands[i]);
		i++;
	}
}
