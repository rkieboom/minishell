/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_document.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 18:06:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/16 21:31:54 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char* addspace(char *str)
{
	char *newstr;
	int length;

	length = ft_strlen(str);
	newstr = ft_calloc(length + 2, sizeof(char));
	if (!str)
		ft_error("Malloc failed!\n");
	ft_strlcpy(newstr, str, length);
	newstr[length] = ' ';
	free (str);
	return (newstr);
}

void	here_document(char *cmd, char *end) //alles wat getypt word moet in de stdin komen. en dan de command uitvoeren
{
	char *newstr;
	char *buf;
	char *temp;

	while(1)
	{
		buf = readline("");
		if (!buf)
			break ;
		if (!ft_strncmp(buf, end, ft_strlen(end) + 1))
		{
			free(buf);
			break ;
		}
		if (!newstr)
			newstr = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(addspace(newstr), buf);
			if (!temp)
				ft_error("ft_strjoin failed!\n");
			free(newstr);
			free(buf);
			newstr = temp;
		}
		if (!newstr)
			ft_error("Malloc failed!\n");
	}
	printf("str = [%s]\n", newstr);
	while(1);
}
