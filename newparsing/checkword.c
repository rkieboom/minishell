/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 15:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/04 17:09:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		calculate_dollar_length(t_list *list, char *str, int *i, int *length)
{
	char *temp;

	if (str[*i + 1] != '?')
	{
		*length += ft_strlen(search_env(list->env, str + *i, 0));
		(*length)--;
		(*i)++;
		while (str[*i] && (ft_isdigit(str[*i]) || \
		ft_isalpha(str[*i]) || (str[*i] == '_')))
			(*i)++;
		(*i)--;
	}
	else
	{
		temp = ft_itoa(g_ret);
		if (!temp)
			ft_ret_exit(1, 1);
		(*length) += ft_strlen(temp);
		free(temp);
		(*i)++;
		(*length)--;
	}
	
}

static int		calculate_length(t_list *list, char *str)
{
	int i;
	int length;

	i = 0;
	length = 0;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i])
	{
		check_quote(list, &str[i]);
		while (str[i] == ' ' && str[i + 1] && \
		list->parse.comma1 == 0 && list->parse.comma2 == 0)
			i++;
		if (str[i] == '$')
		{
			if (!(!ft_isdigit(str[i + 1]) && !ft_isalpha(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?'))
				calculate_dollar_length(list, str, &i, &length);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '$')
					calculate_dollar_length(list, str, &i, &length);
				i++;
				length++;
				list->parse.comma2 = 0;
			}
			length--;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				i++;
				length++;
				list->parse.comma1 = 0;
			}
			length--;
		}
		i++;
		length++;
	}
	return (length);
}

char	*checkword(t_list *list, char *str)
{
	int length;
	char *temp;

	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"')) //dan hoeft er niks veranderd te worden
		return (str);
	length = calculate_length(list, str);
	// printf("Calculating lenght went correct!\n");
	if (length == 0)
	{
		free(str);
		return (ft_strdup("")); //miss lege string returnen
	}
	// printf("Allocated %i Bytes\n", length + 1);
	// printf("It should be %lu Bytes\n", 38 + ft_strlen(search_env(list->env, "$USER", 0)) + ft_strlen(search_env(list->env, "$HOME", 0)) + 1);
	// ft_calloc(length + 1, sizeof(char));
	// if (!newstr)
		// ft_ret_exit(1, 1);
	temp = createstring(list, str, length);
	// printf("Creating string went correct!\n");
	// printf("Str = [%s]-[%zu]\n", temp, ft_strlen(temp));
	free(str);
	return (temp);
}