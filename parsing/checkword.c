/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/24 14:35:45 by mikuiper      ########   odam.nl         */
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
