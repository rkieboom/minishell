/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:34:02 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 17:02:18 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <unistd.h>

int	ft_putstr(char *str);

int	env(t_env *v)
{
	while (v)
	{
		ft_putstr(v->name);
		ft_putstr("=");
		ft_putstr(v->content);
		ft_putstr("\n");
		v = v->next;
	}
	return (0);
}