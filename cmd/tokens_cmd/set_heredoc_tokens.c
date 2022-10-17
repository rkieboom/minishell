/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_heredoc_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 15:13:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 14:10:41 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	get_cmd_count(t_newcommand *temp)
{
	int	c;

	c = 0;
	while (temp)
	{
		temp = temp->next;
		c++;
	}
	return (c);
}

void	set_heredoc_tokens(t_list *list, t_newcommand *cmd, int k)
{
	int	i;
	int	heredoc_c;

	i = 0;
	heredoc_c = 0;
	while (i < list->tokens[k].total)
	{
		if (!ft_strncmp(list->tokens[k].token[i], "|", 2))
		{
			cmd = cmd->next;
		}
		else if (!ft_strncmp(list->tokens[k].token[i], "<<", 3))
		{
			if (!cmd->tokens->heredoc)
				cmd->tokens->heredoc = &list->tokens[k].heredoc[heredoc_c];
			heredoc_c++;
		}
		i++;
	}
}
