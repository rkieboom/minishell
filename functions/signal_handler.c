/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 18:21:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 23:01:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	process(int sign_num)
{
	if (!kill(g_global.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putstr_fd("\n", 2);
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
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_global.status = 1;
		}
	}
}

//Setting the signals
void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

//Setting all signals to IGN
void	signals_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
