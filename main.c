/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 17:01:08 by rkieboom      ########   odam.nl         */
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
		ft_error("get_next_line failed!");
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
	}
}



int			main(int argc, char **argv, char **envp)
{
	t_list list;

	// for(int i = 0; envp[i]; i++)
	// 	printf("%i.[%s]\n", i, envp[i]);
	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	loop(&list);
	return (0);
}
