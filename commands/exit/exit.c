/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 09:15:36 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/15 14:59:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void	ft_exit(int ret, int print)
{
	if (print == 1)
	{
		ft_putstr_fd("minishell-1.0$: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	exit(ret);
}
