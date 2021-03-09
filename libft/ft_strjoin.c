/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:25:35 by rkieboom       #+#    #+#                */
/*   Updated: 2019/11/15 17:23:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copytoresult(char const *s1, char const *s2, char *result)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		result[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		stringlength;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	stringlength = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	result = malloc(sizeof(char) * (stringlength + 1));
	if (result == NULL)
		return (NULL);
	copytoresult(s1, s2, result);
	return (result);
}
