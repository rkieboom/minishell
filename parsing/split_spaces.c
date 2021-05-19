/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_spaces.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 22:08:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/19 13:40:40 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		arraysize(const char *s, char c, t_list *list)
{
	int i;
	int k;

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
		if (s[i] == c && (list->parse.comma1 == 0 && list->parse.comma2 == 0) && i > 0 && s[i - 1] != c)
			k++;
		i++;
	}
	if (i > 0 && s[i - 1] != ' ')
		k++;
	return (k + 1);
}

static void		findstart(const char *s, char c, int *i, int *start)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
		*start = *i;
}

static int		freemem(char **result, int k)
{
	if (!result[k])
	{
		while (k > 0)
		{
			k--;
			free(result[k]);
		}
		free(result);
		return (1);
	}
	return (0);
}

static char		**splitter(t_list *list, const char *str, char c, char **result)
{
	int i;
	int k;
	int length;

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
				k++;
				length = 0;
			}
		}
		i++;
	}
	if (str[i] == '\0')
		result[k] = ft_substr(str, i - length, length);
	return (result);
}

char			**split_spaces(t_list *list, const char *str, char c)
{
	int length;
	char **result;

	if (!str)
		return (NULL);
	length = arraysize(str, c, list);
	result = (char**)malloc(length * sizeof(char *));
	if (!result)
		return (NULL);
	result = splitter(list, str, c, result);
	result[length - 1] = NULL;
	return (result);
}