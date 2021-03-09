/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 16:34:08 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 15:50:24 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkforletter(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
			return (0);
		j++;
	}
	return (1);
}

static int	checkforlastletter(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
			return (0);
		j++;
	}
	return (1);
}

static void	getstring(char const *s1, char const *set, int *i, int *j)
{
	while (s1[*i] != '\0')
	{
		if (checkforletter(s1, set, *i) == 1)
			break ;
		(*i)++;
	}
	while (*j > 0)
	{
		if (checkforlastletter(s1, set, *j) == 1)
			break ;
		(*j)--;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		slength;
	int		i;
	int		j;
	int		k;

	if (!s1)
		return (NULL);
	slength = ft_strlen((char *)s1);
	i = 0;
	j = slength - 1;
	k = 0;
	getstring(s1, set, &i, &j);
	if (j - i + 1 > 0)
		return (ft_substr(s1, i, (j - i + 1)));
	else
		return (ft_strdup(""));
}
