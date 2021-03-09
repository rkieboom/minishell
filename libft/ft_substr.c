/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 11:37:30 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/27 13:14:56 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*result;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (ft_strlen(s) - start < len)
		result = (char*)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (len > 0 && s[start])
	{
		result[i] = s[start];
		start++;
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
