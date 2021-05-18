/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/18 21:53:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../commands.h"

int			skipspaces(const char *str);
// char	*add_new_line(char *str);

static int	checkdollar(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	else
		return (0);
}

static char	*createstring(t_env *v, const char *str, int i, int length)
{
	char	*newstr;

	newstr = NULL;
	while (1)
	{
		while (str[i] && str[i] != '$')
			i++;
		if (!newstr)
			newstr = ft_substr(str, 0, i);
		else if (str[i] == '$')
			newstr = ft_strjoin(newstr, ft_substr(str, 0, i));
		else if (!str[i])
			return (ft_strjoin(newstr, str));
		i++;
		while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i])))
		{
			i++;
			length++;
		}
		newstr = ft_strjoin(newstr, search_env(v, \
		(char *)str + (i - length), length));
		str += i;
		i = 0;
		length = 0;
	}
}

static int	checkoption(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && (str[2] == ' '\
	 || str[2] == '\0' || str[2] == '\t'))
		return (0);
	else
		return (1);
}

static char	*skipecho_checkoption(char *str, int *n)
{
	int	i;

	i = 0;
	str += 4;
	str += skipspaces(str);
	*n = checkoption(str);
	if (*n == 0)
		str += 2;
	str += skipspaces(str);
	return (str + i);
}

int	ft_echo(t_env *v, char *str) //LEAKS FIXEN
{
	int		i;
	int		newline;
	char	*newstr;

	i = 0;
	str = skipecho_checkoption(str, &newline);
	if (checkdollar((char *)str) == 0)
		newstr = ft_strdup(str);
	else
		newstr = createstring(v, str, 0, 0);
	if (newline == 1)
		newstr = add_new_line(newstr);
	write(1, newstr, ft_strlen(newstr));
	return (0);
}