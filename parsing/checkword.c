/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 15:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:51:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//Expands string to new value
char	*checkword(t_list *list, char *str)
{
	int		length;
	char	*temp;

	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	length = checkword_calclen(list, str, 0, 0);
	if (length == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	temp = createstring(list, str, length);
	free(str);
	return (temp);
}
