/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 17:29:09 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

static void	p(t_list *list)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (list->parse.commands[i])
	{
		while (list->parse.commands[i][j])
		{
			check_quote(list, &list->parse.commands[i][j]);
			if (list->parse.comma1 || list->parse.comma2 || list->parse.commands[i][j] == '$')
			{
				if (list->parse.comma1)
					list->parse.commands[i] = single_quote(list, list->parse.commands[i]);
				else if (list->parse.comma2)
					list->parse.commands[i] = double_quote(list, list->parse.commands[i]);
				else
					list->parse.commands[i] = dollar(list, list->parse.commands[i]);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

int	parse(t_list *list)
{
	int	i;

	i = 0;
	list->parse.commands = parse_split(list, ';');
	p(list);
	
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

