/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 14:55:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

static void	p(t_list *list)
{
	int i;

	i = 0;
	while (list->parse.commands[i])
	{
		
	}
}

int	parse(t_list *list)
{
	int	i;

	i = 0;
	list->parse.commands = parse_split(list, ';');
	// parse_check_quotes(list);
	
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
		return (0);
}

void	check_quote(t_list *list, char *c)
{
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
}

void			parse_check_quotes(t_list *list)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (list->parse.commands[i])
	{
		list->parse.comma1 = 0;
		list->parse.comma2 = 0;
		while (list->parse.commands[i][j])
		{
			check_quote(list, &list->parse.commands[i][j]);
			j++;
		}
		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
		{
			read_input(list, 1);
			list->parse.commands[i] = ft_strjoin(add_new_line(list->parse.commands[i]), list->gnl.buf);
		}
		else
			i++;
		j = 0;
	}
}
