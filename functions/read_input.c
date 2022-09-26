/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:37:44 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/25 23:09:06 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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

static void	reset_buf(t_list *list)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
}

static void	print_error(t_list *list)
{
	ft_putstr_fd(\
"minishell-4.2$: unexpected EOF while looking for matching `", 2);
	if (list->parse.comma1)
		ft_putstr_fd("''\n", 2);
	else
		ft_putstr_fd("\"'\n", 2);
}

void	read_input(t_list *list, int option)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	reset_buf(list);
	if (option == 0)
	{
		while (!list->gnl.buf)
		{
			list->gnl.buf = readline("minishell-4.2$ ");
			if (!list->gnl.buf)
				exit(1);
			if (list->gnl.buf && check_spaces(list))
				reset_buf(list);
		}
	}
	else
	{
		list->gnl.buf = readline("> ");
		if (list->gnl.buf == NULL)
			print_error(list);
	}
}
