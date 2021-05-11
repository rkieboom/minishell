/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 14:33:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "header.h"
#include "env_list/env_list.h"

static void	read_input(t_list *list, int ret)
{
	if (list->gnl.buf)
		freebuf(list);
	ret = get_next_line(0, &list->gnl.buf);
	if (ret < 0)
		ft_error("get_next_line failed!", -1);
}

static int	loop(t_list *list)
{
	while (1)
	{
		read_input(list, 1);
		parse(list);
		// print(list);
		execute(list);
		ft_free(list);
		// system("leaks minishell");
	}
}



int			main(int argc, char **argv, char **envp)
{
	t_list list;
	t_env	*env = NULL;
	

	(void)argc;
	(void)argv;
	(void)envp;
	(void)list;
	// for(int i = 0; envp[i]; i++)
	// 	printf("%i.[%s]\n", i, envp[i]);
	create_envp(env, envp);
	// ft_bzero(&list, sizeof(t_list));
	// loop(&list);
	return (0);
}
