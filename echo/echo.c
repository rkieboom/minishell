/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 13:19:08 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static char	createstring(const char *str)
{
	int i;
	int length;
	char *newstr;

	i = 0;

	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (str);
	length = i++;
	printf("length = %d, i = %d", length, i);
	
 //
}

int		ft_echo(const char *str)
{
	int i;

	i = 0;
	createstring(str);





	if (write(1, '\n', 1)== -1)
		return (ft_error("Write Failed!\n", -1));

	return (0);
}