/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 20:17:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/07 16:01:24 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void int_sighandler(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 1);
}

void quit_sighandler(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	signals()//return status???
{
	signal(SIGINT, int_sighandler);
	signal(SIGQUIT, quit_sighandler);
}
