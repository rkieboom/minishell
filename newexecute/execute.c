/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:05:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/21 17:24:35 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute(t_list *list, t_newcommand *v, int k)
{
	int				i;
	t_newcommand	*temp;

	while (list->parse.commands[k])
		k++;
	i = 0;
	while (k)
	{
		temp = &v[i];
		if ((!temp->next && (!temp->tokens || temp->tokens->total == 0)) && temp->command)
			run_commands(list, temp);
		else if (!temp->next)
		{
			if (!redirections(list, temp) && v->command)
				run_cmd_redir(list, temp);
			reset_redirections(list, temp);
		}
		else
			ft_pipes(list, temp);
		i++;
		k--;
	}
}