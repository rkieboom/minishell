/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:56:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 16:45:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
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
