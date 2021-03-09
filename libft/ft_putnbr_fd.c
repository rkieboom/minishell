/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 21:25:53 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/15 17:22:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int number, int fd)
{
	if (number == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		number *= -1;
	}
	if ((number / 10) > 0)
		ft_putnbr_fd(number / 10, fd);
	ft_putchar_fd(((number % 10) + 48), fd);
}
