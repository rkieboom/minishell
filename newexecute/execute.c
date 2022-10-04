/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/10 18:05:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:08:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	go(t_list *list, t_newcommand *temp)
{
	if ((!temp->next && (!temp->tokens || \
	temp->tokens->total == 0)) && temp->command)
		run_cmd(list, temp->command);
	else if (!temp->next)
	{
		if (!get_last_redir(temp, 0, temp->tokens->total))
		{
			if (temp->tokens->heredoc)
				write_to_pipe(temp->tokens->heredoc, \
				temp->tokens->heredoc->data);
			if (!redirections(list, temp) && temp->command)
				run_cmd_redir(list, temp);
			reset_redirections(list, temp);
			if (temp->tokens->heredoc)
				clear_pipe_heredoc(temp->tokens->heredoc);
		}
	}
	else
		ft_pipes(list, temp);
}

void	execute(t_list *list, t_newcommand *v, int k)
{
	int				i;
	t_newcommand	*temp;

	tcsetattr(0, 0, &g_global.termios_save);
	while (list->parse.commands[k])
		k++;
	i = 0;
	while (k)
	{
		temp = &v[i];
		go(list, temp);
		i++;
		k--;
	}
}
