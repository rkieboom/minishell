/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 17:48:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/11 16:05:51 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static char	*create_string(t_list *list, char *str, int length)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(length + 1);
	newstr[length] = 0;
	while (str[i])
	{
		if (str[i] != '\'')
			newstr[i + j] = str[i];
		else
			j--;
		i++;
	}
	return (newstr);
}

static int	calc_length(t_list *list, char *str)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] != '\'')
			length++;
		i++;
	}
	return (length);
}

char	*single_quote(t_list *list, char *str)
{
	char	*newstr;
	int		length;

	length = calc_length(list, str);
	newstr = create_string(list, str, length);
	free(str);
	return (newstr);
}
