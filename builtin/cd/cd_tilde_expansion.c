/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_tilde_expansion.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 19:36:56 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 22:42:12 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static char	*add_home_env(t_env *env, char *str)
{
	int		length;
	char	*home;
	char	*newstr;

	length = 0;
	home = env_get_content(env, "HOME");
	length += ft_strlen(home);
	length += ft_strlen(str);
	newstr = ft_calloc(sizeof(char), length + 1);
	if (!newstr)
		ft_ret_exit(1, 1);
	ft_strlcpy(newstr, home, ft_strlen(home) + 1);
	ft_strlcpy(newstr + ft_strlen(home), str + 1, ft_strlen(str + 1) + 1);
	return (newstr);
}

static int	home_exist(t_env *env)
{
	if (!env_exist(env, "HOME"))
	{
		ft_putendl_fd("minishell-4.2$: cd: HOME not set", 2);
		return (0);
	}
	return (1);
}

int	cd_tilde_expansion(t_list *list, char *str)
{
	int		ret;
	char	*newpath;

	if (!home_exist(list->env) || !env_has_data(list->env, "HOME"))
		return (1);
	if (!str[1])
	{
		newpath = ft_strdup(env_get_content(list->env, "HOME"));
		if (!newpath)
			ft_ret_exit(1, 1);
	}
	else if (str[1] == ':' || str[1] == '/')
		newpath = add_home_env(list->env, str);
	else
		newpath = ft_strdup(str);
	ret = cd_exec_cmd(list->env, newpath);
	free(newpath);
	return (ret);
}
