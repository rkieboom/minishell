/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 21:28:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/05 15:11:54 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;
}				t_vars;

int	array_thingy(int *p)
{
	if (*p == 1)
		*p = 0;
	else if (*p == 0)
		*p = 1;
	return (1);
}

void	free_old_and_set(t_list *list, int k, char **str, char **newstr)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	list->parse.commands[k] = newstr;
}

int	check_char(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[0] == '<') || c[0] == '|')
		return (1);
	return (0);
}

int	check_char_str(t_list *list, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote(list, &str[i]);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}

static void	init_vars(t_vars *vars, int size)
{
	vars->i = 0;
	vars->j = 0;
	vars->x = 0;
	vars->newstr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!vars->newstr)
		ft_ret_exit(1, 1);
	vars->newstr[size] = 0;
}

char	**parse_split_tokens(t_list *list, int size, int k)
{
	t_vars	vars;

	init_vars(&vars, size);
	while (vars.j < size && list->parse.commands[k][vars.j])
	{
		if (!check_char_str(list, list->parse.commands[k][vars.j]))
			vars.newstr[vars.j + vars.x] = ft_strdup(list->parse.commands[k][vars.j]);
		else
		{
			if (check_char(&list->parse.commands[k][vars.j][vars.i]))
				vars.p = 1;
			else
				vars.p = 0;
			vars.start = vars.i;
			while (vars.i < (int)ft_strlen(list->parse.commands[k][vars.j]) && list->parse.commands[k][vars.j][vars.i])
			{
				if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && ((vars.p == 1 && !check_char(&list->parse.commands[k][vars.j][vars.i + 1]) && array_thingy(&vars.p)) || (!list->parse.commands[k][vars.j][vars.i + 1] && array_thingy(&vars.p))))
				{
					if (!list->parse.commands[k][vars.j][vars.i + 1] && ft_strlen(list->parse.commands[k][vars.j]) == 1)
						vars.i++;
					vars.newstr[vars.j + vars.x] = ft_substr(list->parse.commands[k][vars.j], vars.start, vars.i - vars.start + 1);
					vars.start = vars.i + 1;
					vars.x++;	
				}
				else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 && (((vars.p == 0 && check_char(&list->parse.commands[k][vars.j][vars.i + 1]) && array_thingy(&vars.p)))))
				{
					vars.newstr[vars.j + vars.x] = ft_substr(list->parse.commands[k][vars.j], vars.start, vars.i - vars.start + 1);
					vars.start = vars.i + 1;
					vars.x++;
				}
				vars.i++;
			}
			vars.x -= 1;
		}
		vars.i = 0;
		vars.j++;
	}
	free_old_and_set(list, k, list->parse.commands[k], vars.newstr);
	return (NULL);
}
