/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 18:54:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/27 16:09:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**parse_split(t_list *list, char c);
char	**parse_test(t_list *list);

static void	p(t_list *list)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	while (list->parse.commands[i])
	{
		j = 0;
		while (list->parse.commands[i][j])
		{
			k = 0;
			while (list->parse.commands[i][j][k] != '\0')
			{
				check_quote(list, &list->parse.commands[i][j][k]);
				if (list->parse.comma1 || list->parse.comma2 || list->parse.commands[i][j][k] == '$')
				{
					if (list->parse.comma1)
						list->parse.commands[i][j] = single_quote(list, list->parse.commands[i][j]);
					else if (list->parse.comma2)
						list->parse.commands[i][j] = double_quote(list, list->parse.commands[i][j]);
					else
						list->parse.commands[i][j] = dollar(list, list->parse.commands[i][j]);
					k = 0;
					list->parse.comma1 = 0;
					list->parse.comma2 = 0;
				}
				k++;
			}
			j++;
		}
		i++;
	}
}

static void	freemem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	if (result)
		free(result);
}

int		ft_strnstr_i(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needlelength;

	i = 0;
	j = 0;
	needlelength = 0;
	while (needle[needlelength] != '\0')
		needlelength++;
	if (needlelength == 0)
		return (-1);
	while (haystack[i] && i != len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len != j + i)
		{
			j++;
			if (j == needlelength)
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	check_dollar_return_val(t_list *list, char **splitted, char *newstr)
{
	int i;
	int start;
	char *temp;
	char *number;

	i = 0;
	while (splitted[i])
	{
		while (1)
		{
			start = ft_strnstr_i(splitted[i], "$?", ft_strlen(splitted[i])); //moet kijken of in single quote!!!!!!!!
			if (start < 0)
				break ;
			number = ft_itoa(list->ret);
			if (!number)
				return ;//ft_exit
			newstr = ft_substr(splitted[i], 0, ft_strlen(splitted[i]) - ft_strlen(splitted[i] + start));
			if (!newstr)
				return ;//ft_exit
			temp = ft_strjoin(newstr, number);
			if (!temp)
				return ;//ft_exit
			free(newstr);
			free(number);
			newstr = ft_strjoin(temp, splitted[i] + start + 2);
			free(splitted[i]);
			free(temp);
			splitted[i] = newstr;
		}
		i++;
	}
}

int	parse(t_list *list)
{
	int		i;
	int		length;
	char	**splitted;

	i = 0;
	length = 0;
	splitted = parse_split(list, ';');
	check_dollar_return_val(list, splitted, NULL);
	
	list->parse.commands[length] = 0;
	list->tokens = calloc(length, sizeof(t_tokens));
	
	p(list);
	freemem(splitted);
	return (0);
}
