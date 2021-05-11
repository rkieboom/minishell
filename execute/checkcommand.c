/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 16:54:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		ft_echo(const char *str);

static int	findname(const char *str)
{
	int i;

	i = skipspaces(str);
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	return (i);
}

static void	printerror(const char *str)
{
	int length;

	length = findname(str);
	if (write(2, "zsh: command not found: ", 24) == -1)
		exit(1);
	if (write(2, str + skipspaces(str), length) == -1)
		exit(1);
	if (write(2, "\n", 1) == -1)
		exit(1);
}

static int	checkcommand2(const char *str1, const char *str2, int i)
{
	if (ft_strncmp(str1, str2, i) == 0)
		if (str1[i] == ' ' || str1[i] == '\0')
			return (1);
	return (0);
}

void		checkcommand(t_list *list)
{
	int	i;

	i = 0;
	while (list->parse.commands[i])
	{
		if (checkcommand2(list->parse.commands[i], "echo", 4))
			ft_echo(list->parse.commands[i]);
		else if (checkcommand2(list->parse.commands[i], "cd", 2))
			break ;
		else if (checkcommand2(list->parse.commands[i], "pwd", 3))
			break ;
		else if (checkcommand2(list->parse.commands[i], "export", 6))
			break ;
		else if (checkcommand2(list->parse.commands[i], "unset", 5))
			break ;
		else if (checkcommand2(list->parse.commands[i], "env", 3))
			env(list->env);
		else if (checkcommand2(list->parse.commands[i], "exit", 4))
			exit(0);
		else
			printerror(list->parse.commands[i]);
		i++;
	}
}
