/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_pwd_oldpwd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 23:45:51 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/09 15:50:45 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	check_pwd(t_env *env)
{
	char	cwd[4096];
	char	*name;
	char	*content;

	if (!getcwd(cwd, 4096))
		return ;
	name = ft_strdup("PWD");
	if (!name)
		ft_ret_exit(1, 1);
	content = ft_strdup(cwd);
	if (!content)
		ft_ret_exit(1, 1);
	env_lstadd_back(&env, env_lst_new(name, content));
}

static void	check_oldpwd(t_env *env)
{
	char	cwd[4096];
	char	*name;
	char	*content;

	if (!getcwd(cwd, 4096))
		return ;
	name = ft_strdup("OLDPWD");
	if (!name)
		ft_ret_exit(1, 1);
	content = ft_strdup(cwd);
	if (!content)
		ft_ret_exit(1, 1);
	env_lstadd_back(&env, env_lst_new(name, content));
}

void	check_pwd_oldpwd(t_env *env)
{
	if (!ft_strncmp(search_envname_returnenvname(env, "PWD"), "", 1))
		check_pwd(env);
	if (!ft_strncmp(search_envname_returnenvname(env, "OLDPWD"), "", 1))
		check_oldpwd(env);
}
