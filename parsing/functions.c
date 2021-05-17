/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 16:40:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 18:05:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char *single_quote(t_list *list, char *str)
{
	return (ft_substr(str, 1, ft_strlen(str) - 2));
}

static char *create_string(t_list *list, char *str, int length, int strlength)
{
	int i;
	int j;
	int k;
	char *newstr;
	
	i = 0;
	j = 0;
	k = 0;
	newstr = malloc(length);
	if (!newstr)
		return (NULL);
	while (length)
	{
		if (str[i + k] == '$' && j == 0)
		{
			ft_strlcpy(newstr + i, search_env(list->env, str + i + k + 1, strlength), strlength + 1);
			j = strlength;
		}
		else if (str[i + k] != '\"')
			newstr[i + j] = str[i + k];
		if (str[i + k] != '$' && str[i + k] != '\"')
		{
			i++;
			length--;
		}
		else
			k++;
	}
	// free(str);
	return (newstr);
}

char *double_quote(t_list *list, char *str)
{
	char *dup_str;
	int length;
	int strlength;

	strlength = 0;
	length = ft_strlen(str) - 2;
	dup_str = ft_strchr(str, '$');
	if (dup_str)
	{
		dup_str++;
		while (dup_str[strlength] && (ft_isdigit(dup_str[strlength]) || ft_isalpha(dup_str[strlength])))
			strlength++;
		length += ft_strlen(search_env(list->env, dup_str, strlength)) - strlength;
	}
	str = create_string(list, str, length, strlength);
	
	
	return (str);
	








	
	// int i;
	// int	length;
	// int strlength;
	// char *newstr;

	// i = 0;
	// length = 0;
	// strlength = 0;
	// str++;
	// while (str[i])
	// {
	// 	if (str[i] == '$')
	// 		while (str[i + strlength] && (ft_isdigit(str[i + strlength]) || ft_isalpha(str[i + strlength])))
	// 			strlength++;
	// 		length += ft_strlen(search_env(list->env, str + i + 1, strlength))
	// 	i++;
	// 	length++;
	// }
	
}

char *dollar(t_list *list, char *str)
{
	return (NULL);
}
