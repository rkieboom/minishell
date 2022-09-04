/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createstring.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 15:03:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/04 17:09:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

struct vars
{
	int i;
	int x;
	int length;
	char *str;
	char *newstr;
};

static void return_dollar_value(t_list *list, struct vars *vars)
{
	char *temp;

	if (vars->str[vars->i + 1] == '?')
	{
		temp = ft_itoa(g_ret);
		if (!temp)
			ft_ret_exit(1, 1);
		ft_memcpy(vars->newstr + vars->x, temp, ft_strlen(temp));
		vars->length -= ft_strlen(vars->newstr);
		vars->length++;
		while (vars->newstr[vars->x])
			vars->x++;
		vars->x--;
		vars->i++;
	}
	else if (vars->str[vars->i + 1] == '\0' || (!ft_isdigit(vars->str[vars->i + 1]) && !ft_isalpha(vars->str[vars->i + 1]) && vars->str[vars->i + 1] != '_'))
	{
		vars->newstr[vars->x] = '$';
		return ;
	}
	else
	{
		vars->length -= ft_strlen(search_env(list->env, vars->str + vars->i, 0)); //kijken of niet 0 ret
		vars->length++;
		temp = ft_strdup(search_env(list->env, vars->str + vars->i, 0));
		if (!temp)
			ft_ret_exit(1, 1);
		ft_memcpy(vars->newstr + vars->x, temp, ft_strlen(temp));
		while (vars->newstr[vars->x]) //kijken of niet 0?
			vars->x++;
		vars->x--;
		vars->i++;
		while (vars->str[vars->i] && (ft_isdigit(vars->str[vars->i]) || \
		ft_isalpha(vars->str[vars->i]) || (vars->str[vars->i] == '_')))
			vars->i++;
		vars->i--;
	}
	free(temp);
}


char *createstring(t_list *list, char *str, int length)
{
	struct vars vars;

	ft_bzero(&vars, sizeof(vars));
	vars.length = length;
	vars.str = str;
	vars.newstr = ft_calloc(vars.length + 1, sizeof(char));
	if (!vars.newstr)
		ft_ret_exit(1, 1);
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	vars.i = -1;
	while (vars.length > 0)
	{
		vars.i++;
		check_quote(list, &str[vars.i]);
		if (str[vars.i] == '$' && list->parse.comma1 == 0)
			return_dollar_value(list, &vars);
		else if (str[vars.i] == '\"' && ((list->parse.comma1 == 0 && list->parse.comma2 == 1) || (list->parse.comma1 == 0 && list->parse.comma2 == 0)))
			continue;
		else if (str[vars.i] == '\'' && ((list->parse.comma2 == 0 && list->parse.comma1 == 1) || (list->parse.comma1 == 0 && list->parse.comma2 == 0)))
			continue;
		else
			vars.newstr[vars.x] = str[vars.i];
		vars.length--;
		vars.x++;
	}
	// vars.newstr[length] = 0;
	// free(str);
	return (vars.newstr);
}
