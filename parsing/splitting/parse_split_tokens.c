/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:11 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/24 14:35:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;
}				t_vars;

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

static void	init_vars(t_vars *vars, int size)
{
	vars->i = 0;
	vars->j = 0;
	vars->x = 0;
	vars->newstr = ft_calloc(size + 1, sizeof(char *));
	if (!vars->newstr)
		ft_ret_exit(1, 1);
	vars->newstr[size] = 0;
}

static void	func(t_list *list, t_vars *vars, int k)
{
	if (list->parse.comma1 == 0 && list->parse.comma2 == 0 \
	&& ((vars->p == 1 && \
	!check_char(&list->parse.commands[k][vars->j][vars->i + 1]) \
	&& array_thingy(&vars->p)) || (!list->parse.commands[k] \
	[vars->j][vars->i + 1] && array_thingy(&vars->p))))
	{
		if (!list->parse.commands[k][vars->j][vars->i + 1] \
		&& ft_strlen(list->parse.commands[k][vars->j]) == 1)
			vars->i++;
		vars->newstr[vars->j + vars->x] = \
		ft_substr(list->parse.commands[k][vars->j], \
		vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	else if (list->parse.comma1 == 0 && list->parse.comma2 == 0 \
	&& (((vars->p == 0 && check_char(&list->parse.commands[k] \
	[vars->j][vars->i + 1]) && array_thingy(&vars->p)))))
	{
		vars->newstr[vars->j + vars->x] = ft_substr(list-> \
		parse.commands[k][vars->j], vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	vars->i++;
}

//Seperate tokens
//Example: echo hallo>out = echo hallo > out
void	parse_split_tokens(t_list *list, int size, int k)
{
	t_vars	vars;

	init_vars(&vars, size);
	while (vars.j < size && list->parse.commands[k][vars.j])
	{
		if (!check_char_str(list, list->parse.commands[k][vars.j]))
			vars.newstr[vars.j + vars.x] = \
			ft_strdup(list->parse.commands[k][vars.j]);
		else
		{
			if (check_char(&list->parse.commands[k][vars.j][vars.i]))
				vars.p = 1;
			else
				vars.p = 0;
			vars.start = vars.i;
			while (vars.i < (int)ft_strlen(list->parse.commands[k] \
			[vars.j]) && list->parse.commands[k][vars.j][vars.i])
				func(list, &vars, k);
			vars.x -= 1;
		}
		vars.i = 0;
		vars.j++;
	}
	free_old_and_set(list, k, list->parse.commands[k], vars.newstr);
}
