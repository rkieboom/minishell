/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 18:21:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:07:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	process(int sign_num)
{
	if (!kill(g_global.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 131;
		}
		else if (sign_num == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 1;
	}
}

void	sig_handler(int sign_num)
{
	if ((sign_num == SIGINT || \
	sign_num == SIGQUIT) && g_global.pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_global.status = 1;
		}
	}
}
