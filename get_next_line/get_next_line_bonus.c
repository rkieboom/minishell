/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 16:58:51 by rkieboom       #+#    #+#                */
/*   Updated: 2020/01/10 12:05:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int			get_next_line(int fd, char **line)
{
	static t_list	list;
	char			*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		list.ret = read(fd, buf, BUFFER_SIZE);
		if (list.ret == -1)
		{
			free(buf);
			return (-1);
		}
		buf[list.ret] = '\0';
		saveinput(list.result, buf);
		if (list.ret == 0 || findnewline(buf, 1))
			break ;
	}
	free(buf);
	createresult(line, &list);
	if (findnewline(list.result, list.j) != 0)
		return (1);
	resetlist(&list);
	return (0);
}

void		saveinput(char *result, char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (result[i] != '\0')
		i++;
	while (buf[j] != '\0')
	{
		result[i] = buf[j];
		i++;
		j++;
	}
}

void		createresult(char **line, t_list *list)
{
	int start;
	int length;

	start = findnewline(list->result, list->j);
	length = findnewline(list->result, list->j + 1);
	length -= start;
	*line = ft_substr(list->result, start, length - 1);
	list->j++;
}

int			findnewline(char *str, int length)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			j++;
			if (length == j)
				return (i + 1);
		}
		i++;
	}
	return (0);
}
