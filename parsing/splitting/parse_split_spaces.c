/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_spaces.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:06 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/24 14:35:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int	i;
	int	k;
	int	length;
}				t_vars;

static int	arraysize(const char *s, char c, t_list *list)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i = skipspaces(s);
	if (s[i] == '\0')
		return (0);
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
	while (s[i])
	{
		check_quote(list, (char *)s + i);
		if (s[i] == c && \
			(list->parse.comma1 == 0 && list->parse.comma2 == 0) && \
			i > 0 && s[i - 1] != c)
			k++;
		i++;
	}
	if (i > 0 && s[i - 1] != ' ')
		k++;
	return (k);
}

static void	init_vars(t_list *list, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	list->parse.comma1 = 0;
	list->parse.comma2 = 0;
}

static char	**splitter(t_list *list, const char *str, char **result)
{
	t_vars	vars;

	init_vars(list, &vars);
	while (str[vars.i])
	{
		check_quote(list, (char *)str + vars.i);
		if (str[vars.i] != ' ' || list->parse.comma1 || list->parse.comma2)
			vars.length++;
		else
		{
			if (vars.length != 0)
			{
				result[vars.k] = ft_substr \
				(str, vars.i - vars.length, vars.length);
				if (!result[vars.k])
					ft_ret_exit(1, 1);
				vars.k++;
				vars.length = 0;
			}
		}
		vars.i++;
	}
	if (str[vars.i] == '\0' && vars.i > 0 && str[vars.i - 1] != ' ')
		result[vars.k] = ft_substr(str, vars.i - vars.length, vars.length);
	return (result);
}

//Splits on spaces
char	**parse_split_spaces(t_list *list, const char *str, char c)
{
	int		length;
	char	**result;

	if (!str)
		return (NULL);
	length = arraysize(str, c, list);
	result = ft_calloc(length + 1, sizeof(char *));
	if (!result)
		ft_ret_exit(1, 1);
	result = splitter(list, str, result);
	result[length] = NULL;
	return (result);
}
