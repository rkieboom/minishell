/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 18:09:13 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/29 16:05:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t needlelength;

	i = 0;
	j = 0;
	needlelength = 0;
	while (needle[needlelength] != '\0')
		needlelength++;
	if (needlelength == 0)
		return ((char*)haystack);
	while (haystack[i] && i != len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len != j + i)
		{
			j++;
			if (j == needlelength)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
