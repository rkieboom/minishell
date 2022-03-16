/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/10 19:42:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>


static int	loop(t_list *list)
{
	while (1)
	{
		read_input(list, 0);
		check_input_quotes(list);
		add_history(list->gnl.buf);
		check_input(list);
		new_parse(list);
		execute(list);
		free_parse_commands(list);
	}
}

void sighandler(int signum)
{
	printf("Signal '[%i]' was received!\n", signum);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	// signal(SIGABRT, sighandler);
	// signal(SIGTERM, sighandler);
	
	// while(1)
	// 	sleep(1);
	loop(&list);
	return (0);
}
