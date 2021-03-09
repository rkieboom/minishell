/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 16:10:29 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/27 12:38:56 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	long long	posorneg;

	result = 0;
	posorneg = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			posorneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result * 10 + (str[i] - '0')) < result)
			return (((posorneg * -1) - 1) / 2);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)(result * posorneg));
}
