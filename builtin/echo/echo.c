/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/04 16:19:38 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../commands.h"

static void	ft_newlineoption(int *i, int *newlineoption, char **str)
{
	*newlineoption = 0;
	*i = 1;
	if (str[1][0] == '-')
	{
		while (str[1][*i] == 'n')
			(*i)++;
		if (str[1][*i] != '\0')
			*i = 1;
		else
		{
			*i = 2;
			*newlineoption = 1;
		}
	}
}

int	echo(char **str)
{
	int	i;
	int	newlineoption;

	if (!str[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	ft_newlineoption(&i, &newlineoption, str);
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
