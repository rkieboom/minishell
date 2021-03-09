/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:48:59 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/29 06:10:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*src;

	i = 0;
	src = (char*)s;
	while (i < n)
	{
		if (src[i] == c)
			return (&src[i]);
		i++;
	}
	return (0);
}
