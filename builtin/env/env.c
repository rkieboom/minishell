/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:34:02 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/19 20:26:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	env(t_env *v)
{
	while (v)
	{
		if (v->content)
		{
			ft_putstr_fd(v->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(v->content, 1);
			ft_putstr_fd("\n", 1);
		}
		v = v->next;
	}
	return (0);
}
