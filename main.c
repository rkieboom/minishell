/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/21 19:34:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static int check_spaces(t_list *list)
{
	int i;

	i = 0;
	while (list->gnl.buf[i] && (list->gnl.buf[i] == 32 || (list->gnl.buf[i] >= 9 && list->gnl.buf[i] <= 13)))
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
		// if (list->gnl.buf == NULL)
		// 	exit(0);
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
		printf("Before parse");
		fflush(NULL);
		parse(list);
		printf("hier42");
		fflush(NULL);
		execute(list);
		free_parse_commands(list);
	}
}

static int	open_directory(t_list *list)
{
	if (!(list->dir.dir = opendir(".")))
		return (-1);
	// if (!(list->dir.dir = opendir(search_env(list->env, "PWD", 3))))
	// 	if (!(list->dir.dir = opendir(".")))
	// 		return (-1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	// list.stdout_cpy = dup(1);
	// if (open_directory(&list) == -1)
	// 	return (1);
	loop(&list);
	return (0);
} // echo yooo > test.txt
