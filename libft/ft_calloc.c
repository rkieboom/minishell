/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:33:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:54:22 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * (count * size));
	if (result == NULL)
		return (NULL);
	while (i != (count * size))
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
