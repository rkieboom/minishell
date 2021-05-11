/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 16:06:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static char	*createstring(const char *str)
{
	int i;
	int length;
	char *newstr;

	i = 0;

	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return ((char*)str);
	length = i++;
	printf("length = %d, i = %d", length, i);
	
	return (NULL);
}

int		ft_echo(char *str)
{
	int i;

	i = 0;
	// createstring(str);




	write(1, str, ft_strlen(str));
	write(1, "\n", 1);

	return (0);
}