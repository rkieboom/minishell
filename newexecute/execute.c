/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:05:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/23 16:23:32 by rkieboom      ########   odam.nl         */
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
		if (!temp->next && (!temp->tokens || temp->tokens->total == 0))//single command - no tokens
			run_commands(list, temp);
		else if (!temp->next)//single command - with redirections only
		{
			if (!redirections(list, temp))
				run_commands(list, temp);
			reset_redirections(list, temp);
		}
		else
			while (temp)//pipes command
			{
				if (!temp->tokens || temp->tokens->total == 0)
					run_commands(list, temp); //als iets fout gaat break en naar volgende command in pipes
				temp = temp->next;
			}
		i++;
		k--;
	}
}
