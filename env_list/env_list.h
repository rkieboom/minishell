/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:02:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:14:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}				s_env;

s_list	*env_lst_new(void *name, void *content);
void env_lst_add_front(t_list **lst, t_list *new, void *name, void *content);
int env_lstsize(t_list *lst);