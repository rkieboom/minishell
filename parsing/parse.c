/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/20 13:40:15 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

static void	p(t_list *list)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (list->parse.commands[i])
	{
		while (list->parse.commands[i][j])
		{
			while (list->parse.commands[i][j][k])
			{
				check_quote(list, &list->parse.commands[i][j][k]);
				if (list->parse.comma1 || list->parse.comma2 || list->parse.commands[i][j][k] == '$')
				{
					if (list->parse.comma1)
						list->parse.commands[i][j] = single_quote(list, list->parse.commands[i][j]);
					else if (list->parse.comma2)
						list->parse.commands[i][j] = double_quote(list, list->parse.commands[i][j]);
					else
						list->parse.commands[i][j] = dollar(list, list->parse.commands[i][j]);
					k = 0;
					list->parse.comma1 = 0;
					list->parse.comma2 = 0;
				}
				k++;
			}
			k = 0;
			j++;
		}
		i++;
		j = 0;
	}
}

static void		freemem(char **result)
{
	int i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	if (result)
		free(result);
}

int	parse(t_list *list)
{
	int	i;
	int length;
	char **splitted;

	i = 0;
	length = 0;
	splitted = parse_split(list, ';');
	while (splitted[length])
		length++;
	list->parse.commands = (char ***)malloc((length + 1) * sizeof(char **));
	list->parse.commands[length] = 0;
	while (length)
	{
		list->parse.commands[i] = split_spaces(list, splitted[i], ' ');
		length--;
		i++;
	}
	p(list);
	freemem(splitted);
	return (0);
}


// int	checkcomma(t_list *list, char *c)
// {
// 	if (*c != '\'' && *c != '\"')
// 	{
// 		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
// 		{
// 			if (list->parse.comma1 == 1)
// 				return (1);
// 			else if (list->parse.comma2 == 1)
// 				return (2);
// 			else
// 				return (0);
// 		}
// 	}
// 		return (0);
// }

