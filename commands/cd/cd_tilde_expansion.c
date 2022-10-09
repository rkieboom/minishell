/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_tilde_expansion.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 19:36:56 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/09 16:11:43 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static char*	add_home_env(t_list *list, char *str)
{
	int		length;
	char	*home;
	char	*newstr;

	length = 0;
	home = search_env(list->env, "HOME", 4);
	if (!ft_strncmp(home, "", 1))
	{
		ft_putstr_fd("minishell-4.2$: cd: HOME not set\n", 2);
		return (0);
	}
	length += ft_strlen(home);
	length += ft_strlen(str);

	newstr = ft_calloc(sizeof(char), length);
	if (!newstr)
		ft_ret_exit(1, 1);
	ft_strlcpy(newstr, home, ft_strlen(home) + 1);
	ft_strlcpy(newstr + ft_strlen(home), str + 1, ft_strlen(str + 1) + 1);
	return (newstr);
}

char*	cd_tilde_expansion(t_list *list, char *str)
{
	char	*newstr;

	if (!ft_strchr(str, '~'))
		newstr = ft_strdup(str);
	else if (str[0] == '~')
	{
		if (str[1])
		{
			if (str[1] == ':' || str[1] == '/')
				return (add_home_env(list, str));
			else
				newstr = ft_strdup(str);
		}
		else
		{
			if (!ft_strncmp(search_envname_returnenvname(list->env, "HOME"), "", 1))//HOME ENV NOT SET
			{
				ft_putstr_fd("minishell-4.2$: cd: HOME not set\n", 2);
				return (0);
			}
			newstr = ft_strdup(search_env(list->env, "HOME", 4));
		}
	}
	else
		newstr = ft_strdup(str);
	if (!newstr)
		ft_ret_exit(1, 1);
	return (newstr);
}
