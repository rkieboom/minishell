/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/23 12:37:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

static void	loop(t_list *list)
{
	while (1)
	{
		read_input(list, 0);
		check_input_quotes(list);
		add_history(list->gnl.buf);
		check_input(list);
		new_parse(list);
		create_cmd(list, 0);
		execute(list, list->pipecommand, 0);
		free_parse_commands(list);
		list->ret = (unsigned char)list->ret;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	(void)argc;
	(void)argv;
	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	loop(&list);
	return (0);
}
