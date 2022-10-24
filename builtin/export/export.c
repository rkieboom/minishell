/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 14:07:09 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/23 22:51:43 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if ((ft_isalpha(str[0]) || str[0] == '_') && ft_strncmp(str, "", 1) != 0)
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (!str[i] || str[i] == '=')
			return (1);
	}
	ft_putstr_fd("minishell-4.2$: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

static void	get_attr(t_env **env, char *str, int i)
{
	char	*name;
	char	*content;

	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	name = ft_substr(str, 0, i);
	if (!name)
		ft_ret_exit(1, 1);
	if (!str[i])
		content = 0;
	else
	{
		str += i + 1;
		content = ft_substr(str, 0, ft_strlen(str));
		if (!content)
			ft_ret_exit(1, 1);
	}
	if (env_exist(*env, name))
		env_change_content(*env, name, content);
	else
		env_add_content(env, name, content);
	free(name);
	if (content)
		free(content);
}

int	export(t_env **v, char **str)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!str[1])
		export_declare_list(*v);
	else
	{
		while (str[i])
		{
			if (valid_identifier(str[i]))
				get_attr(v, str[i], 0);
			else
				error = 1;
			i++;
		}
	}
	return (error);
}
