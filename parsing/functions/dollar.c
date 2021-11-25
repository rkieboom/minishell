/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 17:50:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/25 19:31:23 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	calculate_length(t_list *list, char *str)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			length += ft_strlen(search_env(list->env, str + i, 0));
			i += env_str_length(str); //blijft vastlopen met echo "$HOME"'$PATH'
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

static char	*createstring(t_list *list, char *str, int length, int i)
{
	int		j;
	int		newstr_counter;
	char	*newstr;

	j = 0;
	newstr_counter = 0;
	newstr = ft_calloc(length + 1, 1);
	while (length > 0)
	{
		if (str[i] == '$')
		{
			newstr_counter += ft_strlcpy(newstr + i + newstr_counter, \
							search_env(list->env, str + i, 0), \
						ft_strlen(search_env(list->env, str + i, 0)) + 1);
			length -= ft_strlen(search_env(list->env, str + i, 0));
			i += env_str_length(str + i);
		}
		else
		{
			newstr[j + newstr_counter] = str[i];
			i++;
			j++;
			length--;
		}
	}
	return (newstr);
}

char	*dollar(t_list *list, char *str)
{
	int		length;
	char	*newstr;

	length = calculate_length(list, str);
	newstr = createstring(list, str, length, 0);
	free(str);
	return (newstr);
}
