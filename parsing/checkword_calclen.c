/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword_calclen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/24 14:36:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	calculate_dollar_length_2(\
t_list *list, char *str, int *i, int *length)
{
	if (str[*i + 1] == '\0' || \
	(!ft_isdigit(str[*i + 1]) && \
	!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_'))
	{
		(*i)++;
		(*length)++;
	}
	else
	{
		*length += ft_strlen(search_env(list->env, str + *i, 0, 0));
		(*length)--;
		(*i)++;
		while (str[*i] && (ft_isdigit(str[*i]) || \
		ft_isalpha(str[*i]) || (str[*i] == '_')))
			(*i)++;
		(*i)--;
	}
}

static void	calculate_dollar_length(\
t_list *list, char *str, int *i, int *length)
{
	char	*temp;

	if (str[*i + 1] && str[*i + 1] == '?')
	{
		temp = ft_itoa(g_global.status);
		if (!temp)
			ft_ret_exit(1, 1);
		(*length) += ft_strlen(temp);
		free(temp);
		(*i)++;
		(*length)--;
	}
	else
		calculate_dollar_length_2(list, str, i, length);
}

static void	double_quote(t_list *list, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			calculate_dollar_length(list, str, i, length);
		else
		{
			(*i)++;
			(*length)++;
		}
		list->parse.comma2 = 0;
	}
	(*length)--;
}

static void	single_quote(t_list *list, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		(*length)++;
		list->parse.comma1 = 0;
	}
	(*length)--;
}

int	checkword_calclen(t_list *list, char *str, int i, int length)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		check_quote(list, &str[i]);
		while (str[i] == ' ' && str[i + 1] && \
		list->parse.comma1 == 0 && list->parse.comma2 == 0)
			i++;
		if (str[i] == '$')
		{
			if (!(!ft_isdigit(str[i + 1]) \
			&& !ft_isalpha(str[i + 1]) \
			&& str[i + 1] != '_' && str[i + 1] != '?'))
				calculate_dollar_length(list, str, &i, &length);
		}
		else if (str[i] == '\"')
			double_quote(list, str, &i, &length);
		else if (str[i] == '\'')
			single_quote(list, str, &i, &length);
		i++;
		length++;
	}
	return (length);
}
