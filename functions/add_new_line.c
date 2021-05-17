/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_new_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 23:34:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 13:28:38 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*add_new_line(char *str)
{
	int		length;
	char	*result;

	length = ft_strlen(str);
	result = malloc(length + 2);
	ft_strlcpy(result, str, length + 1);
	result[length] = '\n';
	result[length + 1] = '\0';
	free(str);
	return (result);
}
