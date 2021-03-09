/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 14:07:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/12/08 14:09:11 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		print(t_list *list)
{
	int i;

	i = 0;
	while (list->parse.commands[i])
	{
		printf("%i. [%s]\n", i, list->parse.commands[i]);
		i++;
	}
}
