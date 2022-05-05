/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 20:17:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/05 20:51:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void int_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
}

void quit_sighandler(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	signals()
{
	signal(SIGINT, int_sighandler);
	signal(SIGQUIT, quit_sighandler);
}