/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:00:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/23 16:53:28 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		length;
	char	**splitted;
}				t_vars;

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

static void	parsing(t_list *list)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (list->parse.commands[j])
	{
		i = 0;
		x = 0;
		while (list->parse.commands[j][i] != NULL)
		{
			list->parse.commands[j][i - x] = \
			checkword(list, list->parse.commands[j][i]);
			if (!list->parse.commands[j][i])
				x++;
			i++;
		}
		j++;
	}
}

static void	init_allocate(t_list *list, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->splitted = parse_split_commands(list, ';');
	while (vars->splitted[vars->length])
		vars->length++;
	list->parse.commands = ft_calloc(vars->length + 1, sizeof(char **));
	if (!list->parse.commands)
		ft_ret_exit(1, 1);
	list->parse.commands[vars->length] = 0;
	list->tokens = calloc(vars->length, sizeof(t_tokens));
	if (!list->tokens)
		ft_ret_exit(1, 1);
}

int	new_parse(t_list *list)
{
	t_vars	vars;

	init_allocate(list, &vars);
	while (vars.length)
	{
		list->parse.commands[vars.i] = \
		parse_split_spaces(list, vars.splitted[vars.i], ' ');
		parse_split_tokens(list, \
		parse_arraysize(list->parse.commands[vars.i], list), vars.i);
		while (list->parse.commands[vars.i][vars.j])
			vars.j++;
		vars.j = 0;
		vars.length--;
		vars.i++;
	}
	tokens(list);
	while (vars.splitted[vars.length])
		vars.length++;
	if (syntax_error_parse(list))
		return (1);
	set_heredoc(list, vars.length);
	freemem(vars.splitted);
	parsing(list);
	return (0);
}
