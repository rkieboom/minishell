/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:51:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:53:20 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*rdst;
	char	*rsrc;
	size_t	i;

	if (!dst && !src)
		return (dst);
	rdst = dst;
	rsrc = (char *)src;
	i = 0;
	if (len > (size_t)rdst - (size_t)rsrc)
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			rdst[i] = rsrc[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
