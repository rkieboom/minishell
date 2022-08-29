/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/08/27 03:22:42 by rkieboom      ########   odam.nl         */
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
		if (check_input(list))
			continue ;
		new_parse(list);
		create_cmd(list, 0);
		if (!syntax_error(list->cmd))
			execute(list, list->cmd, 0);
		free_parse_commands(list);
		list->ret = (unsigned char)list->ret;
	}
}

static void	increase_shlvl(t_list *list)
{
	int		shlvl;
	char	*newnum;

	shlvl = ft_atoi(search_env(list->env, "SHLVL", 5));
	shlvl++;
	newnum = ft_itoa(shlvl);
	if (!newnum)
		ft_ret_exit(1, 1);
	env_change_content(list->env, "SHLVL", newnum);
	free(newnum);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	(void)argc;
	(void)argv;
	ft_bzero(&list, sizeof(t_list));
	list.env = create_envp(list.env, envp);
	increase_shlvl(&list);
	loop(&list);
	return (0);
}
