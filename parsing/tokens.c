/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 14:56:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/30 18:35:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int check_token(t_list *list, char *str, int k)
{
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
	{
		list->tokens[k].
	}
	else if (str[0] == '>' || str[0] == '<')
	{

	}
}

void	tokens(t_list *list, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (list->parse.commands[k][j])
	{
		while (list->parse.commands[k][j][i])
		{
			check_quote(list, &list->parse.commands[k][j][i]);
			if (list->parse.comma1 == 0 && list->parse.comma2 == 0)
				check_token(list, list->parse.commands[k][j], k);
			i++;
		}
		i = 0;
		j++;
	}
