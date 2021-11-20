/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 17:47:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/17 16:00:23 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	ft_strchr_l(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (0);
}

static int	calc_length(t_list *list, char *str)
{
	int		i;
	int		length;
	char	*str_dup;

	i = 0;
	str_dup = ft_strchr(str, '\"') + 1;
	length = ft_strchr_l(str_dup, '\"');
	while (str_dup[i] && str_dup[i] != '\"')
	{
		if (str_dup[i] == '$')
		{
			length += ft_strlen(search_env(list->env, str_dup + i, 0));
			length -= env_str_length(str_dup + i);
			i += env_str_length(str_dup + i) - 1;
		}
		i++;
	}
	i++;
	while (str_dup[i])
	{
		i++;
		length++;
	}
	length += ft_strchr_l(str, '\"');
	return (length);
}

struct s_vars
{
	int		i;
	int		k;
	int		newstr_counter;
	int		comma;
	char	*newstr;
	char	*env;
};

static void	init_and_malloc(struct s_vars *vars, int *length)
{
	vars->i = 0;
	vars->k = 0;
	vars->newstr_counter = 0;
	vars->comma = 2;
	vars->newstr = malloc(*length + 1);
	if (!vars->newstr)
		ft_exit(1, 1);
	vars->newstr[*length] = 0;
	*length += 2;
}

static char	*create_string(t_list *list, char *str, int length)
{
	struct s_vars	vars;

	init_and_malloc(&vars, &length);
	while (length > 0)
	{
		if (vars.comma > 0 && str[vars.i] == '$')
		{
			vars.newstr_counter += \
			ft_strlcpy(vars.newstr + vars.i + vars.k + vars.newstr_counter, \
			search_env(list->env, str + vars.i, 0), \
			ft_strlen(search_env(list->env, str + vars.i, 0)) + 1);
			vars.newstr_counter -= env_str_length(str + vars.i);
			length -= ft_strlen(search_env(list->env, str + vars.i, 0)) - 1;
			vars.i += env_str_length(str + vars.i) - 1;
		}
		else if (vars.comma <= 0 || str[vars.i] != '\"')
			vars.newstr[vars.i + vars.newstr_counter + vars.k] = str[vars.i];
		else
			vars.k--;
		if (str[vars.i] == '\"')
			vars.comma--;
		vars.i++;
		length--;
	}
	return (vars.newstr);
}

char	*double_quote(t_list *list, char *str)
{
	int		i;
	int		length;
	char	*newstr;

	i = 0;
	length = calc_length(list, str);
	newstr = create_string(list, str, length);
	list->parse.comma2 = 0;
	free(str);
	return (newstr);
}
