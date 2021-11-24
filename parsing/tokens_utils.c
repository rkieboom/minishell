/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 16:19:25 by spelle        #+#    #+#                 */
/*   Updated: 2021/11/24 14:25:55 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	array_thingy(int *p)
{
	if (*p == 1)
		*p = 0;
	else if (*p == 0)
		*p = 1;
	return (1);
}

int	check_char(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[0] == '<') || c[0] == '|')
		return (1);
	return (0);
}

int	check_char_str(t_list *list, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote(list, &str[i]);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}

void	free_old_and_set(t_list *list, int k, char **str, char **newstr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	list->parse.commands[k] = newstr;
}

int	split_str_size(char **str, int j)
{
	int	i;

	i = 0;
	if (i += check_char(&str[j][i]))
	{
		if (str[j][i] == '\0')
			return (0);
		else
			return (1);
	}
	else
	{
		while (str[j][i] && !check_char(&str[j][i]))
			i++;
		while (check_char(&str[j][i]))
			i++;
		if (str[j][i] != '\0')
			return (2);
		return (1);
	}
	return (0);
}
