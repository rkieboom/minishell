/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 14:20:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		ft_echo(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		
	}





	if (write(1, '\n', 1)== -1)
		return (ft_error("Write Failed!\n", -1));

	return (0);
}