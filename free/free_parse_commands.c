/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 21:27:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		free_parse_commands(t_list *list)
{
	int i;

	i = 0;
	if (list)
		i = 0;
	if (list->parse.commands)
	{
		while (list->parse.commands[i])
		{
			free(list->parse.commands[i]);
			i++;
		}
		free(list->parse.commands);
	}
}
