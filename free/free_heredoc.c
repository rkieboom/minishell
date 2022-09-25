/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 04:04:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/25 18:03:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_heredoc_data(t_heredoc_data *data)
{
	t_heredoc_data	*tmp;

	while (data)
	{
		if (data->str)
			free(data->str);
		tmp = data->next;
		free(data);
		data = tmp;
	}
}

void	free_heredoc(t_list *list, int totalcommands)
{
	int				i;
	t_newcommand	*temp;

	i = 0;
	while (i < totalcommands)
	{
		temp = &list->cmd[i];
		if (temp && temp->tokens && temp->tokens->heredoc)
		{
			if (temp->tokens->heredoc->data)
				free_heredoc_data(temp->tokens->heredoc->data);
		}
		if (list->tokens[i].heredoc)
			free(list->tokens[i].heredoc);
		i++;
	}
}
