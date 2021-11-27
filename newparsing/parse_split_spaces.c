/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_spaces.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 22:08:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/27 18:40:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	arraysize(const char *s, char c, t_list *list)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i = skipspaces(s);
	if (s[i] == '\0')
		return (0);
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	while (s[i])
	{
		check_quote(list, (char *)s + i);
		if (s[i] == c && \
			(list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			i > 0 && s[i - 1] != c)
			k++;
		i++;
	}
	if (i > 0 && s[i - 1] != ' ')
		k++;
	return (k);
}

static char	**splitter(t_list *list, const char *str, char c, char **result)
{
	int	i;
	int	k;
	int	length;

	i = 0;
	k = 0;
	length = 0;
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	while (str[i])
	{
		check_quote(list, (char *)str + i);
		if (str[i] != ' ' || list->parse.comma1 || list->parse.comma2)
		{
			length++;
		}
		else
		{
			if (length != 0)
			{
				result[k] = ft_substr(str, i - length, length);
				if (!result[k])
					ft_exit(1, 1);
				k++;
				length = 0;
			}
		}
		i++;
	}
	if (str[i] == '\0' && i > 0 && str[i - 1] != ' ')
		result[k] = ft_substr(str, i - length, length);
	return (result);
}

char	**parse_split_spaces(t_list *list, const char *str, char c)
{
	int		length;
	char	**result;

	if (!str)
		return (NULL);
	length = arraysize(str, c, list);
	result = malloc((length + 1) * sizeof(char *));
	if (!result)
		ft_exit(1, 1);
	result = splitter(list, str, c, result);
	result[length] = NULL;
	return (result);
}
