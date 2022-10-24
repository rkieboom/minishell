/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 11:53:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../commands.h"

static int	newline_and_start(char **str, int *newlineoption)
{
	int	s;
	int	i;

	s = 1;
	while (str[s])
	{
		i = 0;
		if (str[s][i] == '-')
		{
			i++;
			if (!str[s][i])
				return (s);
			while (str[s][i] && str[s][i] == 'n')
				i++;
			if (!str[s][i])
				*newlineoption = 1;
			else
				return (s);
		}
		else
			return (s);
		s++;
	}
	return (s);
}

int	echo(char **str)
{
	int	i;
	int	newlineoption;

	newlineoption = 0;
	if (!str[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = newline_and_start(str, &newlineoption);
	while (str[i])
	{
		while (str[i] && !str[i][0])
			i++;
		if (!str[i])
			break ;
		ft_putstr_fd(str[i], 1);
		i++;
		if (str[i])
			ft_putchar_fd(' ', 1);
	}
	if (!newlineoption)
		ft_putchar_fd('\n', 1);
	return (0);
}
