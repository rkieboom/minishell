/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 13:30:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:53:29 by spelle        ########   odam.nl         */
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
	rdest = (char *)dst;
	rsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		rdest[i] = rsrc[i];
		i++;
	}
	return (rdest);
}
