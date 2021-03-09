/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:48:18 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:53:43 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*rdst;
	unsigned char	*rsrc;
	unsigned char	c1;

	rdst = dst;
	rsrc = (unsigned char *)src;
	i = 0;
	c1 = c;
	while (i < n)
	{
		rdst[i] = rsrc[i];
		if (c1 == rsrc[i])
			return (&rdst[i + 1]);
		i++;
	}
	return (0);
}
