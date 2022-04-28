/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:00:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/24 19:48:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//echo $test        $?$?$"Dit is   een test'$USER  '   "'$PWD   '"$HOME    " doei

#include "parse.h"

static void	freemem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	if (result)
		free(result);
}

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

int	parse_arraysize(char **str, t_list *list)
{
	int	i;
	int	j;
	int	p;
	int	length;

	i = 0;
	j = 0;
	p = 0;
	length = 0;
	while (str[j])
	{
		if (check_char_str(list, str[j]) == 0)
			length++;
		else
		{
			length++;
			if (check_char(&str[j][i]))
				p = 1;
			else
				p = 0;
			while (str[j][i])
			{	
				check_quote(list, &str[j][i]);
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && ((p == 1 && !check_char(&str[j][i]) && array_thingy(&p))))
					length++;
				else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && (((p == 0 && check_char(&str[j][i]) && array_thingy(&p)))))
					length++;
				i++;
			}
		}
		i = 0;
		j++;
	}
	return (length);
}

void	new_parse(t_list *list)
{
	int i;
	int j;
	int length;
	char **splitted;

	i = 0;
	j = 0;
	length = 0;
	splitted = parse_split_commands(list, ';');
	while (splitted[length])
		length++; 
	list->parse.commands = (char ***)malloc((length + 1) * sizeof(char **));
	list->parse.commands[length] = 0;
	list->tokens = calloc(length, sizeof(t_tokens));
	while (length)
	{
		list->parse.commands[i] = parse_split_spaces(list, splitted[i], ' ');
		parse_split_tokens(list, parse_arraysize(list->parse.commands[i], list), i);// gaat wss goed
		while (list->parse.commands[i][j])
			j++;

		j = 0;
		//hier tokens herkennen en in struct aangeven. Nog een nieuwe dynamische struct maken ook eerst!
		length--;
		i++;
	}
	freemem(splitted);
	tokens(list);
	// for(int j = 0; list->parse.commands[j]; j++)
	// 	for(int k = 0; list->parse.commands[j][k]; k++)
	// 		printf("%i. %s\n", k, list->parse.commands[j][k]);
	// while(1);
	parsing(list);
}
