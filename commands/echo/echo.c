/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:14:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 17:35:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		skipspaces(const char *str);

static char	*createstring(const char *str)
{
	int		i;
	int		length;
	char	*newstr;
	i = 0;
	while(str[i] && str[i] != '$')
		i++;
	if(!str[i])
		return ((char *)str);
	length = i++;
	printf("length = %d, i = %d", length, i);
	return (NULL);
}
static int	checkoption(char *str)
{
	int	i;
	if (str[i] == '-' && str[i + 1] == 'n' && (str[i + 2] == ' ' || str[i + 2] == '\0'))
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
	if (*n == 1)
		str += 2;
	str += skipspaces(str);
	return (str + i);
}
static int	checkdollar(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	else
		return (0);
}
int	ft_echo(char *str)
{
	int	i;
	int	n;
	i = 0;
	str = skipecho(str, &n);
	// checkdollar(str);
	createstring(str);
	return (0);
}