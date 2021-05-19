/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/19 11:55:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../commands.h"

int	ft_echo(t_list *v, char **str) //LEAKS FIXEN
{
	int i;

	i = 0;

	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		i++;	
	}
	return (0);
}