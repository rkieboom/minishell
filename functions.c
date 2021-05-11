/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:56:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 17:03:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}
