/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 21:28:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/30 01:35:13 by rkieboom      ########   odam.nl         */
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

char	**parse_split_tokens(t_list *list, int size, int k)
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;

	i = 0;
	j = 0;
	x = 0;
	newstr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!newstr)
		return (NULL);
	newstr[size] = 0;
	while (j < size && list->parse.commands[k][j])
	{
		if (!check_char_str(list, list->parse.commands[k][j]))
			newstr[j + x] = ft_strdup(list->parse.commands[k][j]);
		else
		{
			if (check_char(&list->parse.commands[k][j][i]))
				p = 1;
			else
				p = 0;
			start = i;
			while (i < (int)ft_strlen(list->parse.commands[k][j]) && list->parse.commands[k][j][i])
			{
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && ((p == 1 && !check_char(&list->parse.commands[k][j][i + 1]) && array_thingy(&p)) || (!list->parse.commands[k][j][i + 1] && array_thingy(&p))))
				{
					if (!list->parse.commands[k][j][i + 1] && ft_strlen(list->parse.commands[k][j]) == 1)
						i++;
					newstr[j + x] = ft_substr(list->parse.commands[k][j], start, i - start + 1);
					start = i + 1;
					x++;	
				}
				else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && (((p == 0 && check_char(&list->parse.commands[k][j][i + 1]) && array_thingy(&p)))))
				{
					newstr[j + x] = ft_substr(list->parse.commands[k][j], start, i - start + 1);
					start = i + 1;
					x++;
				}
				i++;
			}
			x -= 1;
		}
		i = 0;
		j++;
	}
	free_old_and_set(list, k, list->parse.commands[k], newstr);
	return (NULL);
}