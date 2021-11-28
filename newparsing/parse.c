/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:00:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/28 19:24:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//echo $test        $?$?$"Dit is   een test'$USER  '   "'$PWD   '"$HOME    " doei

#include "parse.h"

void	parsing(t_list *list)
{
	int i;
	int j;
	int x;

	j = 0;
	x = 0;
	while (list->parse.commands[j])
	{
		i = 0;
		x = 0;
		while (list->parse.commands[j][i] != NULL)
		{
			list->parse.commands[j][i - x] = checkword(list, list->parse.commands[j][i]);
			if (!list->parse.commands[j][i])
				x++;
			i++;
		}
		j++;
	}
}

void	new_parse(t_list *list)
{
	int i;
	int length;
	char **splitted;

	i = 0;
	length = 0;
	splitted = parse_split_commands(list, ';');
	while (splitted[length])
		length++;
	list->parse.commands = (char ***)malloc((length + 1) * sizeof(char **));
	list->parse.commands[length] = 0;
	while (length)
	{
		list->parse.commands[i] = parse_split_spaces(list, splitted[i], ' ');
		length--;
		i++;
	}
	parsing(list);
}