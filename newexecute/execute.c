/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:05:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/21 03:22:28 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	go(t_list *list, t_newcommand *temp, t_newcommand *v)
{
	if ((!temp->next && (!temp->tokens || \
	temp->tokens->total == 0)) && temp->command)
		run_cmd(list, temp->command);
	else if (!temp->next)
	{
		get_last_redir(temp, 0, temp->tokens->total);
		if (temp->tokens->double_redirection_left > 0 && \
		!ft_strncmp(temp->command[v->tokens->last_l], "<<", 3))
			run_cmd_heredoc(list, temp);
		else
		{
			if (!redirections(list, temp) && temp->command)
				run_cmd_redir(list, temp);
			reset_redirections(list, temp);
		}
	}
	else
		ft_pipes(list, temp);
}

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
		go(list, temp, v);
		i++;
		k--;
	}
}
