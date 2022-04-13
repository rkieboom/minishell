/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/13 18:38:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

// void sighandler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else if (signum == SIGQUIT)
// 	{
// 		ft_putchar_fd('\r', 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }


static int	loop(t_list *list)
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
		// ft_bzero(&list->gnl, sizeof(t_gnl));
		// ft_bzero(&list->parse, sizeof(t_parse));
		// ft_bzero(&list->pipecommand, sizeof(t_newcommand));
		// ft_bzero(&list->tokens, sizeof(t_tokens));
		// ft_bzero(list, sizeof(t_list));
		// system("leaks minishell");
		// exit(1);
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
