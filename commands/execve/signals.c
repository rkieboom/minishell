/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 20:17:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/27 18:16:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void	int_sighandler(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 1);
	g_ret = 130;
}

void	quit_sighandler(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 1);
	g_ret = 131;
}

void	signals(void)
{
	signal(SIGINT, int_sighandler);
	signal(SIGQUIT, quit_sighandler);
}
