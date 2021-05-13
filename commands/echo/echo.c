/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/13 14:27:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
# include "../commands.h"

int		skipspaces(const char *str);
static int	checkdollar(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	else
		return (0);
}
static char *add_new_line(char *str)
{
	int length;
	char *result;
	length = ft_strlen(str);
	result = malloc(length + 2);
	ft_strlcpy(result, str, length + 1);
	result[length] = '\n';
	result[length + 1] = '\0';
	free(str);
	return (result);
}
static char	*createstring(t_env *v, const char *str, int n)
{
	int		i;
	int		length = 0;
	char	*newstr = NULL;
	i = 0;
	if (checkdollar((char*)str) == 0)
		ft_strdup(str);
	while (1)
	{
		while(str[i] && str[i] != '$')
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
		newstr = ft_strjoin(newstr, search_env(v, (char*)str + (i - length), length));
		str += i;
		i = 0;
		length = 0;
	}
	return (NULL);
}
static int	checkoption(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && (str[2] == ' ' || str[2] == '\0')) //miss tab
		return (0);
	else
		return (1);
}
static char	*skipecho(char *str, int *n)
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
int	ft_echo(t_env *v, char *str)
{
	int	i;
	int	newline;
	char *newstr;
	i = 0;
	str = skipecho(str, &newline);
	// write(1, "test", 4);
	// write(1, str, ft_strlen(str));
	// str = malloc(length + n)
	newstr = createstring(v, str, newline);
	if (newline == 1)
		newstr = add_new_line(newstr);
	write(1, newstr, ft_strlen(newstr));
	return (0);
}