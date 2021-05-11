/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:55:27 by spelle        #+#    #+#                 */
/*   Updated: 2021/05/11 15:47:39 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

#include <stdlib.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

void	env_lst_add_front(t_env **lst, t_env *new);
t_env	*env_lst_new(void *name, void *content);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstclear(t_env **lst, void (*del)(void*));
t_env	*env_lstlast(t_env *lst);
int		env_lstsize(t_env *lst);

t_env *create_envp(t_env *v, char **envp);

#endif