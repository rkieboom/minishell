/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 14:56:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/08 16:49:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	**split(t_list *list, int size, int k)
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;

	i = 0;
	j = 0;
	x = 0;
	newstr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!newstr)
		return (NULL);
	newstr[size] = 0;
	while (j < size && list->parse.commands[k][j])
	{
		if (!check_char_str(list, list->parse.commands[k][j]))
			newstr[j + x] = ft_strdup(list->parse.commands[k][j]);
		else
		{
			if (check_char(&list->parse.commands[k][j][i]))
				p = 1;
			else
				p = 0;
			start = i;
			while (list->parse.commands[k][j][i])
			{
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && ((p == 1 && !check_char(&list->parse.commands[k][j][i + 1]) && array_thingy(&p)) || (!list->parse.commands[k][j][i + 1] && array_thingy(&p))))
				{
					if (!list->parse.commands[k][j][i + 1] && ft_strlen(list->parse.commands[k][j]) == 1)
						i++;
					newstr[j + x] = ft_substr(list->parse.commands[k][j], start, i - start + 1);
					start = i + 1;
					x++;	
				}
				else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && (((p == 0 && check_char(&list->parse.commands[k][j][i + 1]) && array_thingy(&p)))))
				{
					newstr[j + x] = ft_substr(list->parse.commands[k][j], start, i - start + 1);
					start = i + 1;
					x++;
				}
				i++;
			}
			x -= 1;
		}
		i = 0;
		j++;
	}
	free_old_and_set(list, k, list->parse.commands[k], newstr);
	return (NULL);
}

static int	arraysize(char **str, t_list *list)
{
	int	i;
	int	j;
	int	p;
	int	length;

	i = 0;
	j = 0;
	p = 0;
	length = 0;
	while (str[j])
	{
		if (check_char_str(list, str[j]) == 0)
			length++;
		else
		{
			length++;
			if (check_char(&str[j][i]))
				p = 1;
			else
				p = 0;
			while (str[j][i])
			{	
				check_quote(list, &str[j][i]);
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && ((p == 1 && !check_char(&str[j][i]) && array_thingy(&p))))
					length++;
				else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && (((p == 0 && check_char(&str[j][i]) && array_thingy(&p)))))
					length++;
				i++;
			}
		}
		i = 0;
		j++;
	}
	return (length);
}

void	identify_tokens(t_list *list)
{
	int i;
	int j;

	i = 0;
	while (list->parse.commands[i])
	{
		j = 0;
		while (j < list->tokens[i].total)
		{
			if (!ft_strncmp(list->tokens[i].token[j], "<<", 3))
				list->tokens[i].double_redirection_left = 1;
			else if (!ft_strncmp(list->tokens[i].token[j], ">>", 3))
				list->tokens[i].double_redirection_right = 1;
			else if (!ft_strncmp(list->tokens[i].token[j], "<", 2))
				list->tokens[i].single_redirection_left = 1;
			else if (!ft_strncmp(list->tokens[i].token[j], ">", 2))
				list->tokens[i].single_redirection_right = 1;
			j++;
		}
		i++;
	}
}

void	tokens(t_list *list, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	split(list, arraysize(list->parse.commands[k], list), k);
	while (list->parse.commands[k][j])
	{
		if (check_char(list->parse.commands[k][j]))
		{
			ft_strlcpy(list->tokens[k].token[list->tokens[k].id], list->parse.commands[k][j], ft_strlen(list->parse.commands[k][j]) + 1);
			list->tokens[k].token_pos[list->tokens[k].id] = j;
			list->tokens[k].id++;
		}
		j++;
	}
	list->tokens[k].total = list->tokens[k].id;
	list->tokens[k].id = 0;
	identify_tokens(list);
}
