/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createstring.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 15:03:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:51:39 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		x;
	int		length;
	char	*str;
	char	*newstr;
	char	*temp;
}				t_vars;

static void	return_ret_status(t_vars *vars)
{
	vars->temp = ft_itoa(g_global.status);
	if (!vars->temp)
		ft_ret_exit(1, 1);
	ft_memcpy(vars->newstr + vars->x, vars->temp, ft_strlen(vars->temp));
	vars->length -= ft_strlen(vars->newstr);
	vars->length++;
	while (vars->newstr[vars->x])
		vars->x++;
	vars->x--;
	vars->i++;
}

static void	set_env_value(t_list *list, t_vars *vars)
{
	vars->length -= ft_strlen(\
	search_env(list->env, vars->str + vars->i, 0, 0));
	vars->length++;
	vars->temp = ft_strdup(search_env(list->env, vars->str + vars->i, 0, 0));
	if (!vars->temp)
		ft_ret_exit(1, 1);
	ft_memcpy(vars->newstr + vars->x, vars->temp, ft_strlen(vars->temp));
	while (vars->newstr[vars->x])
		vars->x++;
	vars->x--;
	vars->i++;
	while (vars->str[vars->i] && (ft_isdigit(vars->str[vars->i]) || \
	ft_isalpha(vars->str[vars->i]) || (vars->str[vars->i] == '_')))
		vars->i++;
	vars->i--;
}

static void	return_dollar_value(t_list *list, t_vars *vars)
{
	if (vars->str[vars->i + 1] == '?')
		return_ret_status(vars);
	else if (vars->str[vars->i + 1] == '\0' || \
	(!ft_isdigit(vars->str[vars->i + 1]) && \
	!ft_isalpha(vars->str[vars->i + 1]) && vars->str[vars->i + 1] != '_'))
	{
		vars->newstr[vars->x] = '$';
		return ;
	}
	else
		set_env_value(list, vars);
	free(vars->temp);
}

static void	init_vars(t_list *list, t_vars *vars, int length, char *str)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->length = length;
	vars->str = str;
	vars->newstr = ft_calloc(vars->length + 1, sizeof(char));
	if (!vars->newstr)
		ft_ret_exit(1, 1);
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	vars->i = -1;
}

char	*createstring(t_list *list, char *str, int length)
{
	t_vars	vars;

	init_vars(list, &vars, length, str);
	while (vars.length > 0)
	{
		vars.i++;
		check_quote(list, &str[vars.i]);
		if (str[vars.i] == '$' && list->parse.comma1 == 0)
			return_dollar_value(list, &vars);
		else if (str[vars.i] == '\"' && ((list->parse.comma1 == 0 \
		&& list->parse.comma2 == 1) || (list->parse.comma1 == 0 \
		&& list->parse.comma2 == 0)))
			continue ;
		else if (str[vars.i] == '\'' && ((list->parse.comma2 == 0 \
		&& list->parse.comma1 == 1) || (list->parse.comma1 == 0 \
		&& list->parse.comma2 == 0)))
			continue ;
		else
			vars.newstr[vars.x] = str[vars.i];
		vars.length--;
		vars.x++;
	}
	return (vars.newstr);
}
