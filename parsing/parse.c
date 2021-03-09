/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 13:45:33 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char			**parse_split(t_list *list, char c);

int		parse(t_list *list)
{
	list->parse.commands = parse_split(list, ';');
	
	return (0);
}
