/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_chars.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 00:55:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/06 00:55:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_char(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[0] == '<') || c[0] == '|')
		return (1);
	return (0);
}

int	check_char_str(t_list *list, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote(list, &str[i]);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}
