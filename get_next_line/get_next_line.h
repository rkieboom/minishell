/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 16:58:56 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 17:04:50 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 50
# include <limits.h>
# include <stdio.h>

typedef struct s_list
{
	char		result[INT_MAX];
	int			j;
	int			ret;
}				t_list;

int		get_next_line(int fd, char **line);

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);

void	saveinput(char *result, char *buf);
void	createresult(char **line, t_list *list);
int		findnewline(char *str, int length);
void	resetlist(t_list *list);

#endif
