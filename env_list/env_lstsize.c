/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstsize.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:14:38 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/02 16:17:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int env_lstsize(s_env *lst)
{
	int i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}