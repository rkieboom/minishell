/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:55:27 by spelle        #+#    #+#                 */
/*   Updated: 2022/05/04 12:03:32 by rkieboom      ########   odam.nl         */
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
}					t_env;

void	env_lst_add_front(t_env **lst, t_env *new);
t_env	*env_lst_new(void *name, void *content);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstclear(t_env **lst, void (*del)(void*));
t_env	*env_lstlast(t_env *lst);
int		env_lstsize(t_env *lst);

t_env	*create_envp(t_env *v, char **envp);

void	env_change_content(t_env *v, char *envname, char *envcontent);
char	*search_env(t_env *v, char *name, int length);
char	*search_envname_returnenvname(t_env *v, char *envname);

void	ft_ret_exit(int ret, int print);

#endif