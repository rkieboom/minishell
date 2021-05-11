/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 21:45:09 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

int	parse(t_list *list)
{
	list->parse.commands = parse_split(list, ';');
	// lit->parse.commands = parse_test();
	return (0);
}

int	checkcomma(t_list *list, char *c)
{
	if (*c != '\'' && *c != '\"')
	{
		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
		{
			if (list->parse.comma1 == 1)
				return (1);
			else if (list->parse.comma2 == 1)
				return (2);
			else
				return (0);
		}
	}
	if (*c == '\'')
	{
		if (list->parse.comma1 == 0 && list->parse.comma2 == 0)
			list->parse.comma1 = 1;
		else
			list->parse.comma1 = 0;
	}
	if (*c == '\"')
	{
		if (list->parse.comma2 == 0 && list->parse.comma1 == 0)
			list->parse.comma2 = 1;
		else
			list->parse.comma2 = 0;
	}
		return (0);
}

// void			checkspecialchar(t_list *list, int i, int j)
// {
// 	if (list->parse.commands[i][j] == '$')
// 	{
		
// 	}
// }

// char			**parse_test(t_list *list)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (list->parse.commands[i])
// 	{
// 		while (list->parse.commands[i][j])
// 		{
// 			if (checkcomma(list, list->gnl.buf[i]) != 1) //kijken voor comma.
// 				checkspecialchar(list, i, j); //Als het niet "\'" dan kijken voor special char
				
// 			j++:
// 		}
// 		i++;
// 		j = 0;
// 	}
// }
