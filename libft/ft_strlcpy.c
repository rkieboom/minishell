/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:40:56 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/29 06:37:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	k;

	if (!src || !dst)
		return (0);
	else if (dstsize == 0)
		return (ft_strlen(src));
	k = 0;
	while (k < (dstsize - 1) && src[k] != '\0')
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (ft_strlen(src));
}
