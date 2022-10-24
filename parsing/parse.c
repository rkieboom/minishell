/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:00:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:32:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		length;
	char	**splitted;
}				t_vars;

//Free the temporily struct
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

//The actual big parsing and expanding
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

//Splits on ';'
//Allocate and set all values to 0
static void	init_allocate(t_list *list, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	//Tilde expansion here
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

//str + 1 = \0 || ' ' || ':' || '/' THEN Expand tilde if HOME exists

// (1) scans input and allocates memory
// (2) adjusts input for easy parsing
// (3) extracts and stores tokens
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
		vars.length--;
		vars.i++;
	}
	tokens(list);
	while (vars.splitted[vars.length])
		vars.length++;
	if (syntax_error_parse(list))
	{
		freemem(vars.splitted);
		return (1);
	}
	allocate_heredoc(list, vars.length);
	freemem(vars.splitted);
	parsing(list);
	set_heredoc(list, vars.length);
	return (0);
}
