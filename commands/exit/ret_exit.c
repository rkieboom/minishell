/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ret_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 09:15:36 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/04 12:03:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void	ft_ret_exit(int ret, int print)
{
	if (print == 1)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	exit(ret);
}
