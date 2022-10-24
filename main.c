/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:40:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 14:09:47 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

t_global	g_global;

//Loop where minishell will be in continous
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
				execution(list, list->cmd, 0);
		}
		free_all(list);
	}
}

//Increases the ENV SHLVL
static void	increase_shlvl(t_list *list)
{
	int		shlvl;
	char	*newnum;

	if (!list->env)
		return ;
	if (!env_exist(list->env, "SHLVL") && !env_has_data(list->env, "SHLVL"))
		return ;
	shlvl = ft_atoi(env_get_content(list->env, "SHLVL"));
	shlvl++;
	newnum = ft_itoa(shlvl);
	if (!newnum)
		ft_ret_exit(1, 1);
	env_change_content(list->env, "SHLVL", newnum);
	free(newnum);
}

//Handles SIGUSR1 SIGNAL
static void	sighand(int signum)
{
	(void)signum;
	if (g_global.__dup__ == 1)
	{
		g_global.__dup__ = 0;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// Fixing signals in multiple minishells
static void	fix_signals(t_env **env)
{
	signal(SIGUSR1, sighand);
	if (env_exist(*env, __DUP__))
	{
		g_global.__dup__ = 1;
		env_lst_remove(env, __DUP__);
	}
	kill(g_global.pid, SIGUSR1);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	list;

	(void)argc;
	(void)argv;
	ft_bzero(&list, sizeof(t_list));
	ft_bzero(&g_global, sizeof(t_global));
	list.env = create_envp(list.env, envp);
	fix_signals(&list.env);
	increase_shlvl(&list);
	tcgetattr(0, &g_global.termios_save);
	g_global.termios_new = g_global.termios_save;
	g_global.termios_new.c_lflag &= ~ECHOCTL;
	loop(&list);
	return (0);
}
