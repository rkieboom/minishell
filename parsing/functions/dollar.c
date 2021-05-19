/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 17:50:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/19 19:47:54 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	env_str_length(char *str)
{
	int i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i])))
		i++;
	return (i);
}

static int calculate_length(t_list *list, char *str)
{
	int i;
	int length;

	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			length += ft_strlen(search_env(list->env, str + i, 0));
			i += env_str_length(str);
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

static char *createstring(t_list *list, char *str, int length)
{
	int i;
	int newstr_counter;
	char *newstr;

	i = 0;
	newstr_counter = 0;
	newstr = malloc(length + 1);
	newstr[length] = 0;
	while (length > 0)
	{
		if (str[i] == '$')
		{
			newstr_counter += ft_strlcpy(newstr + i + newstr_counter, search_env(list->env, str + i, 0), ft_strlen(search_env(list->env, str + i, 0)) + 1); //lenghte van env
			length -= ft_strlen(search_env(list->env, str + i, 0));
			i += env_str_length(str + i) - 1;
		}
		else
		{
			newstr[i + newstr_counter] = str[i];
			i++;
			length--;
		}
	}
	return (newstr);
}

char *dollar(t_list *list, char *str)
{
	int length;
	char *newstr;

	length = calculate_length(list, str);
	newstr = createstring(list, str, length);
	return (newstr);
}
