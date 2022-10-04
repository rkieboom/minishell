/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 00:01:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:24:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

t_global	g_global;

static void	loop(t_list *list)
{
	while (1)
	{
		read_input(list, 0);
		check_input_quotes(list);
		if (!list->gnl.buf)
			continue ;
		add_history(list->gnl.buf);
		if (check_input(list))
			continue ;
		if (!new_parse(list) && g_global.heredoc_break == 0)
		{
			create_cmd(list, 0);
			if (!syntax_error(list->cmd, 0))
				execute(list, list->cmd, 0);
		}
		free_all(list);
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
	ft_bzero(&g_global, sizeof(t_global));
	list.env = create_envp(list.env, envp);
	increase_shlvl(&list);
	tcgetattr(0, &g_global.termios_save);
	g_global.termios_new = g_global.termios_save;
	g_global.termios_new.c_lflag &= ~ECHOCTL;
	loop(&list);
	return (0);
}
