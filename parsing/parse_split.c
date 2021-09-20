/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 13:58:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/20 13:25:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			checkcomma(t_list *list, char *c);

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
		if (s[i] == c && (list->parse.comma1 == 0 && list->parse.comma2 == 0))
			k++;
		while (s[i] && s[i] == c)
			i++;
		i++;
	}
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
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

static char		**splitter(t_list *list, char c, char **result, int i)
{
	int strlength;
	int arrayindex;
	int start;

	strlength = 0;
	arrayindex = 0;
	while (arrayindex != arraysize(list->gnl.buf, c, list))
	{
		findstart(list->gnl.buf, c, &i, &start);
		while (list->gnl.buf[i] && (list->gnl.buf[i] != c || (list->parse.comma1 == 1 || list->parse.comma2 == 1)))
		{
			check_quote(list, &list->gnl.buf[i]);
			i++;
			strlength++;
		}
		result[arrayindex] = ft_substr(list->gnl.buf, start, strlength);
		if (freemem(result, arrayindex))
			return (NULL);
		strlength = 0;
		arrayindex++;
		i++;
	}
	result[arrayindex] = NULL;
	return (result);
}

char			**parse_split(t_list *list, char c)
{
	char **result;

	if (!list->gnl.buf)
		return (NULL);
	result = (char**)malloc((arraysize(list->gnl.buf, c, list) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = splitter(list, c, result, 0);
	return (result);
}
