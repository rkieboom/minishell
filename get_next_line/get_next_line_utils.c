/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 16:58:53 by rkieboom       #+#    #+#                */
/*   Updated: 2020/01/10 12:02:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*result;

	result = malloc((1 + ft_strlen(s1)) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
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

void		resetlist(t_list *list)
{
	int i;

	i = 0;
	while (list->result[i] != '\0')
	{
		list->result[i] = '\0';
		i++;
	}
	list->j = 0;
}
