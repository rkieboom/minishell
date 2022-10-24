/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:54:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 22:54:01 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/**
 * 
 * Making and editing env list
 * 
**/

t_env	*env_lst_new(void *name, void *content);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lstlast(t_env *lst);
int		env_lstsize(t_env *lst);
void	env_lst_remove(t_env **v, char *find);

t_env	*create_envp(t_env *v, char **envp);

/**
 * 
 * Functions
 * 
**/

char	*env_get_name(t_env *v, char *find);
char	*env_get_content(t_env *v, char *find);
void	env_add_content(t_env **v, char *envname, char *envcontent);
void	env_change_content(t_env *v, char *envname, char *envcontent);
t_env	*env_get(t_env *v, char *find);
int		env_has_data(t_env *v, char *find);
int		env_exist(t_env *v, char *find);

void	ft_ret_exit(int ret, int print);

#endif