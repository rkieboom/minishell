/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_create_str.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 21:21:20 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:50:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int		i;
	int		j;
	char	*newstr;
	char	*temp;
}				t_vars;

static void	found_dollar_sign(t_list *list, t_vars *vars, char *str)
{
	vars->i++;
	if (str[vars->i] \
	&& (ft_isalnum(str[vars->i]) \
	|| str[vars->i] == '_'))
	{
		vars->temp = search_env(list->env, str + vars->i, 0, 0);
		vars->j += ft_strlcpy(\
		vars->newstr + vars->j, \
		vars->temp, ft_strlen(vars->temp) + 1);
		while (str[vars->i] \
		&& (ft_isalnum(str[vars->i]) \
		|| str[vars->i] == '_'))
			vars->i++;
	}
	else
	{
		vars->newstr[vars->j] = str[vars->i - 1];
		vars->j++;
	}
}

char	*heredoc_create_str(t_list *list, char *str, int length)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	vars.newstr = ft_calloc(length + 1, sizeof(char));
	if (!vars.newstr)
		ft_ret_exit(1, 1);
	while (str[vars.i])
	{
		if (str[vars.i] == '$')
			found_dollar_sign(list, &vars, str);
		else
		{
			vars.newstr[vars.j] = str[vars.i];
			vars.i++;
			vars.j++;
		}
	}
	free(str);
	vars.newstr[length] = 0;
	return (vars.newstr);
}
