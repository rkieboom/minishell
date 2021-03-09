/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 13:30:29 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/27 12:48:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*rdest;
	char	*rsrc;
	size_t	i;

	if (!dst && !src)
		return (dst);
	rdest = (char*)dst;
	rsrc = (char*)src;
	i = 0;
	while (i < n)
	{
		rdest[i] = rsrc[i];
		i++;
	}
	return (rdest);
}
