/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:00:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/27 19:13:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//echo $test        $?$?$"Dit is   een test'$PDW  '   "'$PWD   '"$HOME    " doei

#include "parse.h"

void		calculate_dollar_length(t_list *list, char *str, int *i, int *length)
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
		temp = ft_itoa(list->ret);
		if (!temp)
			ft_exit(1, 1);
		(*length) += ft_strlen(temp);
		free(temp);
		(*i)++;
		(*length)--;
	}
	
}

int		calculate_length(t_list *list, char *str)
{
	int i;
	int p;
	int length;

	i = 0;
	p = 0;
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
	char *newstr;

	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"')) //dan hoeft er niks veranderd te worden
		return (str);
	length = calculate_length(list, str);
	if (length == 0)
		return (0);
	ft_calloc(length + 1, sizeof(char));
	if (!newstr)
		ft_exit(1, 1);
	//createstring();
	free(str);
	return (newstr);
}

void	parsing(t_list *list)
{
	int i;
	int j;
	int x;

	j = 0;
	x = 0;
	while (list->parse.commands[j])
	{
		i = 0;
		while (list->parse.commands[j][i])
		{
			list->parse.commands[j][i - x] = checkword(list, list->parse.commands[j][i]);
			if (!list->parse.commands[j][i])
				x++;
			i++;
		}
		j++;
	}
}

void	new_parse(t_list *list)
{
	int i;
	int length;
	char **splitted;

	i = 0;
	length = 0;
	splitted = parse_split_commands(list, ';');
	while (splitted[length])
		length++;
	list->parse.commands = (char ***)malloc((length + 1) * sizeof(char **));
	while (length)
	{
		list->parse.commands[i] = parse_split_spaces(list, splitted[i], ' ');
		length--;
		i++;
	}
	parsing(list);
}