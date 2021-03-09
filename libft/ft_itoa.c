/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 15:32:52 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/19 19:37:50 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mallocsize(int n)
{
	int j;

	j = 0;
	if (n < 0)
	{
		n = n * -1;
		j++;
	}
	if (n == 0)
		j++;
	while (n > 0)
	{
		n = n / 10;
		j++;
	}
	return (j);
}

static void	ft_conversion(char *result, int n, int i)
{
	result[ft_mallocsize(n)] = '\0';
	i = ft_mallocsize(n) - 1;
	if (n < 0)
	{
		n = n * -1;
		result[0] = '-';
	}
	if (n == 0 || n == -0)
		result[0] = '0';
	while (n > 0)
	{
		result[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

char		*ft_itoa(int n)
{
	int		i;
	char	*result;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc(sizeof(char) * ft_mallocsize(n) + 1);
	if (result == NULL)
		return (NULL);
	ft_conversion(result, n, i);
	return (result);
}
