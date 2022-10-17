/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 21:00:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 14:15:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
		else
			return (WTERMSIG(status));
	}
	return (1);
}
