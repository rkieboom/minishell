/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 14:07:09 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/03 12:21:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	invalid_identifier(char *str)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (1);
}

static int	check_error(char **str, int i, int *j, int *error)
{
	*j = 0;
	while ((str[i][*j] && str[i][*j] != '=') || *j == 0)
	{
		if (!ft_isalnum(str[i][*j]) && str[i][*j] != '_')
		{
			*error = invalid_identifier(str[i]);
			return (1);
		}
		(*j)++;
	}
	return (0);
}

static void	set_env_name_and_content(t_env *v, char **str, int i, int j)
{
	char	*envname;
	char	*envcontent;

	envcontent = NULL;
	envname = ft_substr(str[i], 0, j);
	if (!envname)
		ft_ret_exit(1, 1);
	if (ft_strchr(str[i], '=') == NULL)
		envcontent = ft_strdup("");
	else
		envcontent = ft_strdup(ft_strchr(str[i], '=') + 1);
	if (!envcontent)
		ft_ret_exit(1, 1);
	if (!ft_strncmp(search_envname_returnenvname(v, envname), "", 1))
		env_lstadd_back(&v, env_lst_new(envname, envcontent));
	else
	{
		env_change_content(v, envname, envcontent);
		free(envname);
		free(envcontent);
	}
}

int	export(t_env *v, char **str)
{
	int		i;
	int		j;
	int		error;

	error = 0;
	if (str[1] == NULL)
	{
		export_declare_list(v);
	}
	i = 1;
	while (str[i] != NULL)
	{
		if (!check_error(str, i, &j, &error))
			set_env_name_and_content(v, str, i, j);
		i++;
	}
	return (error);
}
