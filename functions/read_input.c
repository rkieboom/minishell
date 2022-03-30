/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:37:44 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/16 17:51:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void sighandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("sig=[%i]\n", sig); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
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

void	read_input(t_list *list, int option)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (option == 0)
	{
		while (!list->gnl.buf)
		{
			list->gnl.buf = readline("minishell-4.2$ ");
			if (!list->gnl.buf)
				exit(0);
			if (list->gnl.buf && check_spaces(list))
			{
				free(list->gnl.buf);
				list->gnl.buf = 0;
			}
		}
	}
	else
	{
		list->gnl.buf = readline("> ");
		if (list->gnl.buf == NULL)
			ft_exit(1, 1);
	}
}
