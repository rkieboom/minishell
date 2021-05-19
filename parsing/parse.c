/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/19 14:02:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

// static void	p(t_list *list)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (list->parse.commands[i])
// 	{
// 		while (list->parse.commands[i][j])
// 		{
// 			check_quote(list, &list->parse.commands[i][j]);
// 			if (list->parse.comma1 || list->parse.comma2 || list->parse.commands[i][j] == '$')
// 			{
// 				if (list->parse.comma1)
// 					list->parse.commands[i] = single_quote(list, list->parse.commands[i]);
// 				else if (list->parse.comma2)
// 					list->parse.commands[i] = double_quote(list, list->parse.commands[i]);
// 				else
// 					list->parse.commands[i] = dollar(list, list->parse.commands[i]);
// 			}
// 			j++;
// 		}
// 		i++;
// 		j = 0;
	// }
// }

static char *fix_spaces(char *str)
{
	return (NULL);
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
	while (length)
	{
		list->parse.commands[i] = split_spaces(list, splitted[i], ' ');
		length--;
		i++;
	}
	// p(list);
	
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

