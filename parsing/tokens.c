/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 14:56:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/02 14:28:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static	int	check_char(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[1] == '>') || c[0] == '|')
		return (1);
	return (0);
	
}

static	int	check_char_str(t_list *list, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		check_quote(list, &str[i]);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && ((str[i] == '>' && str[i] == '>') || (str[i] == '<' && str[i] == '<')))
			return (2);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && ((str[i] == '>' || str[i] == '>') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
	
}

static void	free_old_and_set(t_list *list, int k, char **str, char **newstr)
{
	int i;
	int j;

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

static char **split(t_list *list, int size, int k)
{
	int i;
	int j;
	int start;
	char **newstr;

	i = 0;
	j = 0;
	newstr = (char**)malloc(sizeof(char *) * (size + 1));
	if (!newstr)
		return (NULL);
	newstr[size] = 0;
	while (j < 4 && list->parse.commands[k][j])
	{
		if (!check_char_str(list, list->parse.commands[k][j]))
			newstr[j] = ft_strdup(list->parse.commands[k][j]);
		else
		{
			while (list->parse.commands[k][j][i])
			{
				start = 0;
				check_quote(list, &list->parse.commands[k][j][i]);
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && check_char(&list->parse.commands[k][j][i]))
				{
					// if (i == 0)
					// 	j--;
					newstr[j] = ft_substr(list->parse.commands[k][j], 0, i + 1);
					i++;
					start = check_char(&list->parse.commands[k][j][i]) + i;
					if (list->parse.commands[k][j][start] && start - i == 0)
						newstr[j + 1] = ft_strdup(&list->parse.commands[k][j][start]);
					else
					{
						newstr[j + 2] = ft_strdup(&list->parse.commands[k][j][start]);
						newstr[j + 1] = ft_substr(list->parse.commands[k][j], i, start - i);
					}
					if (list->parse.commands[k][j][start])
						j++;
					j += 2;
					break;
				}
				i++;
			}
			i = 0;
		}
		j++;
	}
	free_old_and_set(list, k, list->parse.commands[k], newstr);
	return (NULL);
}

static	int	split_str_size(char **str, int j)
{
	int i;

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

static	int	arraysize(char **str, t_list *list)
{
	int i;
	int j;
	int length;

	i = 0;
	j = 0;
	length = 0;
	while (str[length])
		length++;
	while (str[j])
	{
		while (str[j][i])
		{
			check_quote(list, &str[j][i]);
			if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && check_char(&str[j][i]))
				return (length += split_str_size(str, j));
			i++;
		}
		i = 0;
		j++;
	}
	return (length);
}

void	tokens(t_list *list, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;

	split(list, arraysize(list->parse.commands[k], list), k);
	while (list->parse.commands[k][j])
	{
		if (check_char(list->parse.commands[k][j]))
		{
			ft_strlcpy(list->tokens[k].token[list->tokens[k].id], list->parse.commands[k][j], ft_strlen(list->parse.commands[k][j]));
			list->tokens[k].token_pos[list->tokens[k].id] = j;
			list->tokens[k].id++;
		}
		j++;
	}
	list->tokens[k].total = list->tokens[k].id;
	list->tokens[k].id = 0;
}
