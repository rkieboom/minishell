/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/10 18:08:18 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../commands.h"

int	echo(char **str)
{
	int	i;
	int	newlineoption;

	i = 1;
	newlineoption = 0;
	if (str[i] && !ft_strncmp(str[i], "-n", 3))
	{
		i++;
		newlineoption = 1;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		i++;
		if (str[i])
			ft_putchar_fd(' ', 1);
	}
	if (!newlineoption)
		ft_putchar_fd('\n', 1);
	return (0);
}
