/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/20 21:16:55 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	check_spaces(t_list *list)
{
	int	i;

	i = 0;
	while (list->gnl.buf[i] && (list->gnl.buf[i] == 32 \
	|| (list->gnl.buf[i] >= 9 && list->gnl.buf[i] <= 13)))
		i++;
	if (list->gnl.buf[i])
		return (0);
	return (1);
}

void	read_input(t_list *list, int option)
{
	if (option == 0)
	{
		while (!list->gnl.buf)
		{
			list->gnl.buf = readline("minishell-1.0$ ");
			if (!list->gnl.buf)
				write(1, "\n", 1);
			else if (!list->gnl.buf || check_spaces(list))
			{
				free(list->gnl.buf);
				list->gnl.buf = 0;
			}
		}
	}
	else
	{
		list->gnl.buf = readline("> ");
		if (list->gnl.buf == NULL)
			ft_exit(1, 1);
	}
}

static void	check_input(t_list *list)
{
	char	*newstr;
	int		i;

	i = 0;
	while (1)
	{
		list->parse.comma1 = 0;
		list->parse.comma2 = 0;
		while (list->gnl.buf[i])
		{
			check_quote(list, &list->gnl.buf[i]);
			i++;
		}
		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
		{
			newstr = ft_strdup(list->gnl.buf);
			read_input(list, 1);
			list->gnl.buf = ft_strjoin(add_new_line(newstr), list->gnl.buf);
		}
		else
			break ;
		i = 0;
	}
}

static int	loop(t_list *list)
{
	while (1)
	{
		read_input(list, 0);
		check_input(list);
		add_history(list->gnl.buf);
		parse(list);
		execute(list);
		free_parse_commands(list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	loop(&list);
	return (0);
}
